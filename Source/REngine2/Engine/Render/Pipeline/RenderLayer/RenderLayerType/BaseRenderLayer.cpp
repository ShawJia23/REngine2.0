#include"BaseRenderLayer.h"
#include"../../../../ViewPort/ViewportInfo.h"
#include"../../../../Component/RComponentMinimal.h"
#include"../../BufferView/ConstantBufferView.h"
#include"../../../ConstontBuffer/ObjectTransformation.h"
#include"../../Geometry/RenderMeshData.h"
#include"../../Geometry/GeometryMap.h"
#include"../../../../World.h"
#include"../../../../Camera/Camera.h"

RenderLayer::RenderLayer():RenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE)
{

}

RenderLayer::~RenderLayer()
{

}

void RenderLayer::InitRenderLayer(RDXPipelineState* inPipelineState, RGeometryMap* inGeometryMap)
{
	m_PipelineState = inPipelineState;
	m_GeometryMap = inGeometryMap;
}

void RenderLayer::PostDraw()
{
	vector<vector<std::weak_ptr<RRenderData>>::const_iterator> RemoveRenderingData;
	for (vector<std::weak_ptr<RRenderData>>::const_iterator Iter = m_RenderDatas.begin();
		Iter != m_RenderDatas.end();
		++Iter)
	{
		if (Iter->expired())
		{
			RemoveRenderingData.push_back(Iter);
		}
	}

	for (auto& Tmp : RemoveRenderingData)
	{
		m_RenderDatas.erase(Tmp);
	}
}

void RenderLayer::BuildPSO()
{
	BuildShader();

	m_PipelineState->Build();
}

void RenderLayer::BuildShaderMacro(std::vector<RShaderMacro>& inMacro)
{
	{
		RShaderMacro shaderMacro;

		char TextureNumBuff[10] = { 0 };
		shaderMacro.Name = "TEXTURE2D_MAP_NUM";
		shaderMacro.Definition = _itoa(m_GeometryMap->GetTextureNumber(), TextureNumBuff, 10);

		inMacro.push_back(shaderMacro);
	}

	{
		RShaderMacro shaderMacro;

		char TextureNumBuff[10] = { 0 };
		shaderMacro.Name = "CUBE_MAP_NUM";
		shaderMacro.Definition = _itoa(m_GeometryMap->GetCubeMapNumber(), TextureNumBuff, 10);

		inMacro.push_back(shaderMacro);
	}
}

void RenderLayer::DrawMesh()
{
	m_PipelineState->ResetPSO((int)RenderLayerType);
	for (auto& inRenderData : m_RenderDatas)
	{
		DrawMesh(inRenderData);
	}
}

void RenderLayer::DrawMesh(std::weak_ptr<RRenderData>& geometry)
{
	if (geometry.expired())
		return;

	if (!geometry.lock()->Mesh->IsVisible())
		return;

	auto pFrustum=GetWorld()->GetCamera()->GetBoundingFrustum();
	if(!pFrustum.Contains(geometry.lock()->Bounds))
		return;

	UINT MeshOffset = m_GeometryMap->GetObjectConstantBufferView().GetConstantBufferByteSize();

	auto pRenderData = geometry.lock();

	D3D12_GPU_VIRTUAL_ADDRESS FirstVirtualMeshAddress = m_GeometryMap->GetObjectConstantBufferView().GetBuffer()->GetGPUVirtualAddress();
	D3D12_VERTEX_BUFFER_VIEW VBV = m_GeometryMap->GetRGeometry(pRenderData->GeometryIndex).GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW IBV = m_GeometryMap->GetRGeometry(pRenderData->GeometryIndex).GetIndexBufferView();

	GetCommandList()->IASetIndexBuffer(&IBV);

	//绑定渲染流水线上的输入槽，可以在输入装配器阶段传入顶点数据
	GetCommandList()->IASetVertexBuffers(
		0,//起始输入槽 0-15 
		1,//k k+1 ... k+n-1 
		&VBV);

	//定义我们要绘制的哪种图元 点 线 面
	EMaterialDisplayStatue pDisplayState = (*pRenderData->Mesh->GetMaterials())[0]->GetMaterialDisplayState();
	GetCommandList()->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)pDisplayState);

	D3D12_GPU_VIRTUAL_ADDRESS VAddress =
		FirstVirtualMeshAddress + pRenderData->ObjectIndex * MeshOffset;

	GetCommandList()->SetGraphicsRootConstantBufferView(0, VAddress);

	GetCommandList()->DrawIndexedInstanced(
		pRenderData->IndexSize,//顶点数量
		1,//绘制实例数量
		pRenderData->IndexOffsetPosition,//顶点缓冲区第一个被绘制的索引
		pRenderData->VertexOffsetPosition,//GPU 从索引缓冲区读取的第一个索引的位置。
		0);//在从顶点缓冲区读取每个实例数据之前添加到每个索引的值。
}

void RenderLayer::UpdateCalculations(const ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView)
{
	XMMATRIX ViewMatrix = XMLoadFloat4x4(&viewportInfo.ViewMatrix);
	XMMATRIX ProjectMatrix = XMLoadFloat4x4(&viewportInfo.ProjectMatrix);

	for (size_t i = 0; i < GetRenderDataSize(); i++)
	{
	    auto pRenderData = m_RenderDatas[i];
		if (pRenderData.expired())
			continue;
		//构造模型的world
		{
			XMFLOAT3& Position = pRenderData.lock().get()->Mesh->GetPosition();
			fvector_3d Scale = pRenderData.lock().get()->Mesh->GetScale();

			XMFLOAT3 RightVector = pRenderData.lock().get()->Mesh->GetRightVector();
			XMFLOAT3 UPVector = pRenderData.lock().get()->Mesh->GetUPVector();
			XMFLOAT3 ForwardVector = pRenderData.lock().get()->Mesh->GetForwardVector();

			pRenderData.lock().get()->WorldMatrix = {
				RightVector.x * Scale.x,	UPVector.x,				ForwardVector.x ,			0.f,
				RightVector.y,				UPVector.y * Scale.y,	ForwardVector.y,			0.f,
				RightVector.z,				UPVector.z ,			ForwardVector.z * Scale.z,	0.f,
				Position.x,					Position.y,				Position.z,					1.f };
		}

		//更新模型位置
		XMMATRIX ATRIXWorld = XMLoadFloat4x4(&pRenderData.lock().get()->WorldMatrix);
		XMMATRIX ATRIXTextureTransform = XMLoadFloat4x4(&pRenderData.lock().get()->TextureTransform);
		XMVECTOR AATRIXWorldDeterminant = DirectX::XMMatrixDeterminant(ATRIXWorld);
		XMMATRIX NormalInverseMatrix = DirectX::XMMatrixInverse(&AATRIXWorldDeterminant, ATRIXWorld);

		RObjectTransformation ObjectTransformation;
		XMStoreFloat4x4(&ObjectTransformation.World, DirectX::XMMatrixTranspose(ATRIXWorld));
		XMStoreFloat4x4(&ObjectTransformation.TextureTransformation, DirectX::XMMatrixTranspose(ATRIXTextureTransform));
		XMStoreFloat4x4(&ObjectTransformation.NormalTransformation, NormalInverseMatrix);
		//收集材质Index
		if (auto& InMater = (*pRenderData.lock().get()->Mesh->GetMaterials())[0])
		{
			ObjectTransformation.MaterialIndex = InMater->GetMaterialIndex();
		}

		objectConstantBufferView.Update(pRenderData.lock().get()->ObjectIndex, &ObjectTransformation);
	}
}

void RenderLayer::SetRenderLayerType(EMeshRenderLayerType type) 
{ 
	RenderLayerType = type; 
}
void RenderLayer::AddRenderData(std::weak_ptr<RRenderData> data)
{
	m_RenderDatas.push_back(data);
}
void RenderLayer::RemoveRenderData(std::weak_ptr<RRenderData> data)
{
	if (!data.expired())
	{
		for (vector<std::weak_ptr<RRenderData>>::const_iterator Iter = m_RenderDatas.begin();
			Iter != m_RenderDatas.end();
			++Iter)
		{
			if (!Iter->expired())
			{
				if (Iter->lock() == data.lock())
				{
					m_RenderDatas.erase(Iter);
					break;
				}
			}
		}
	}
}
void RenderLayer::Clear()
{
	m_RenderDatas.clear();
}
EMeshRenderLayerType RenderLayer::GetRenderLayerType() const 
{ 
	return RenderLayerType;
}
vector<std::weak_ptr<RRenderData>> RenderLayer::GetRenderDatas()
{ 
	return m_RenderDatas;
}
UINT RenderLayer::GetRenderDataSize()
{ 
	return m_RenderDatas.size();
}