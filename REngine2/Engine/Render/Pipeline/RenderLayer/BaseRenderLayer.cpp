#include"BaseRenderLayer.h"
#include"../../../Core/ViewPort/ViewportInfo.h"
#include"../../../Component/RComponentMinimal.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../ConstontBuffer/ObjectTransformation.h"
#include"../Geometry/RenderMeshData.h"

RenderLayer::RenderLayer():RenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE)
{

}

void RenderLayer::BuildPipelineState(UINT TextureSize,ID3D12RootSignature* rootSignature)
{
    m_PipelineState.ResetGPSDesc();
    BuildShader(TextureSize);
    m_PipelineState.BindRootSignature(rootSignature);
    m_PipelineState.Build();
}

void RenderLayer::CaptureKeyboardKeys()
{
    m_PipelineState.CaptureKeyboardKeys();
}

void RenderLayer::ResetCommandList()
{
    m_PipelineState.ResetCommandList();
}

void RenderLayer::DrawMesh(map<int, RGeometry*> geometrys, ID3D12DescriptorHeap* heap)
{
	UINT m_DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	for (auto& Tmp : m_RenderDatas) 
	{
		D3D12_VERTEX_BUFFER_VIEW VBV = geometrys[Tmp->GeometryIndex]->GetVertexBufferView();
		D3D12_INDEX_BUFFER_VIEW IBV = geometrys[Tmp->GeometryIndex]->GetIndexBufferView();

		GetCommandList()->IASetIndexBuffer(&IBV);

		//绑定渲染流水线上的输入槽，可以在输入装配器阶段传入顶点数据
		GetCommandList()->IASetVertexBuffers(
			0,//起始输入槽 0-15 
			1,//k k+1 ... k+n-1 
			&VBV);

		//定义我们要绘制的哪种图元 点 线 面
		EMaterialDisplayStatue pDisplayState = (*Tmp->Mesh->GetMaterials())[0]->GetMaterialDisplayState();
		GetCommandList()->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)pDisplayState);

		auto DesMeshHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart());
		DesMeshHandle.Offset(Tmp->ObjectIndex, m_DescriptorOffset);
		GetCommandList()->SetGraphicsRootDescriptorTable(0, DesMeshHandle);

		GetCommandList()->DrawIndexedInstanced(
			Tmp->IndexSize,//顶点数量
			1,//绘制实例数量
			Tmp->IndexOffsetPosition,//顶点缓冲区第一个被绘制的索引
			Tmp->VertexOffsetPosition,//GPU 从索引缓冲区读取的第一个索引的位置。
			0);//在从顶点缓冲区读取每个实例数据之前添加到每个索引的值。
	}

}

void RenderLayer::UpdateCalculations(const ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView)
{
	XMMATRIX ViewMatrix = XMLoadFloat4x4(&viewportInfo.ViewMatrix);
	XMMATRIX ProjectMatrix = XMLoadFloat4x4(&viewportInfo.ProjectMatrix);

	for (size_t i = 0; i < GetRenderDataSize(); i++)
	{
		RRenderData* pRenderData = m_RenderDatas[i];

		//构造模型的world
		{
			XMFLOAT3& Position = pRenderData->Mesh->GetPosition();
			fvector_3d Scale = pRenderData->Mesh->GetScale();

			XMFLOAT3 RightVector = pRenderData->Mesh->GetRightVector();
			XMFLOAT3 UPVector = pRenderData->Mesh->GetUPVector();
			XMFLOAT3 ForwardVector = pRenderData->Mesh->GetForwardVector();

			pRenderData->WorldMatrix = {
				RightVector.x * Scale.x,	UPVector.x,				ForwardVector.x ,			0.f,
				RightVector.y,				UPVector.y * Scale.y,	ForwardVector.y,			0.f,
				RightVector.z,				UPVector.z ,			ForwardVector.z * Scale.z,	0.f,
				Position.x,					Position.y,				Position.z,					1.f };
		}

		//更新模型位置
		XMMATRIX ATRIXWorld = XMLoadFloat4x4(&pRenderData->WorldMatrix);
		XMMATRIX ATRIXTextureTransform = XMLoadFloat4x4(&pRenderData->TextureTransform);

		RObjectTransformation ObjectTransformation;
		XMStoreFloat4x4(&ObjectTransformation.World, XMMatrixTranspose(ATRIXWorld));
		XMStoreFloat4x4(&ObjectTransformation.TextureTransformation, XMMatrixTranspose(ATRIXTextureTransform));
		//收集材质Index
		if (auto& InMater = (*pRenderData->Mesh->GetMaterials())[0])
		{
			ObjectTransformation.MaterialIndex = InMater->GetMaterialIndex();
		}

		objectConstantBufferView.Update(pRenderData->ObjectIndex, &ObjectTransformation);
	}
}

void RenderLayer::SetRenderLayerType(EMeshRenderLayerType type) 
{ 
	RenderLayerType = type; 
}
void RenderLayer::AddRenderData(RRenderData* data) 
{
	m_RenderDatas.push_back(data);
}


EMeshRenderLayerType RenderLayer::GetRenderLayerType() const 
{ 
	return RenderLayerType;
}
vector<RRenderData*> RenderLayer::GetRenderDatas() 
{ 
	return m_RenderDatas;
}
UINT RenderLayer::GetRenderDataSize()
{ 
	return m_RenderDatas.size();
}