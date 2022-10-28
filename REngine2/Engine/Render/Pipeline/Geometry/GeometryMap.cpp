#include"GeometryMap.h"
#include"../../../Mesh/Base/ObjectTransformation.h"
#include"../../../Core/ViewPort/ViewportTransform.h"
#include"../../Buffer/ConstructBuffer.h"
#include"../../../Mesh/Base/Mesh.h"
#include"../../../Mesh/Materials/MaterialConstantBuffer.h"
#include"../../../Component/Light/LightConstantBuffer.h"
#include"../../../Mesh/Materials/Material.h"
#include"../../../Component/Mesh/Core/MeshComponent.h"
RGeometryMap::RGeometryMap()
:m_WorldMatrix(RMath::IdentityMatrix4x4())
, IndexSize(0)
{
	
}

void RGeometryMap::Init() 
{
	m_DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void RGeometryMap::BuildDescriptorHeap()
{
	m_DescriptorHeap.Build(GetMeshNumber() + GetMaterialsNumber() + GetLightsNumber() + 1);
}

void RGeometryMap::BuildConstantBufferView()
{
	BuildMeshConstantBufferView();
	BuildMaterialsConstantBufferView();
	BuildLightsConstantBufferView();
	BuildViewportConstantBufferView();
}

void RGeometryMap::BuildMeshConstantBufferView()
{
	m_ObjectConstantBufferView.CreateConstant(sizeof(RObjectTransformation), GetMeshNumber());

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_ObjectConstantBufferView.BuildConstantBuffer(DesHandle, GetMeshNumber());
}

void RGeometryMap::BuildMaterialsConstantBufferView()
{
	m_MaterialsBufferView.CreateConstant(sizeof(RMaterialConstantBuffer), GetMaterialsNumber());

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_MaterialsBufferView.BuildConstantBuffer(DesHandle, GetMaterialsNumber(), GetMeshNumber());
}

void RGeometryMap::BuildLightsConstantBufferView()
{
	m_LightsBufferView.CreateConstant(sizeof(RLightConstantBuffer), 1);

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_LightsBufferView.BuildConstantBuffer(DesHandle, GetLightsNumber(), GetMeshNumber() + GetMaterialsNumber());
}

void RGeometryMap::BuildViewportConstantBufferView()
{
	m_ViewportConstantBufferView.CreateConstant(sizeof(ViewportTransformation), 1);

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_ViewportConstantBufferView.BuildConstantBuffer(DesHandle, 1, GetMeshNumber()+ GetMaterialsNumber()+GetLightsNumber());
}


UINT RGeometryMap::GetMeshNumber()
{
	return m_Geometrys[0].GetDrawObjectNumber();
}

UINT RGeometryMap::GetMaterialsNumber()
{
	UINT pMatereials = 0;
	for (auto& pGeo : m_Geometrys) 
	{
		for (auto& pRenderData : pGeo.second.m_RenderDatas)
		{
			pMatereials+=pRenderData.Mesh->GetMaterialsNum();
		}
	}
	return pMatereials;
}

UINT RGeometryMap::GetLightsNumber()
{
	return 1;
}



void RGeometryMap::Draw() 
{
	DrawViewport();
	DrawLights();
	DrawMesh();
}

void RGeometryMap::DrawLights()
{
	m_DescriptorHeap.SetDescriptorHeap();

	auto DesHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
	DesHandle.Offset(GetMeshNumber() + GetMaterialsNumber() , m_DescriptorOffset);

	GetCommandList()->SetGraphicsRootDescriptorTable(3, DesHandle);
}

void RGeometryMap::DrawViewport()
{
	m_DescriptorHeap.SetDescriptorHeap();

	auto DesHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
	DesHandle.Offset(GetMeshNumber()+GetMaterialsNumber()+GetLightsNumber(), m_DescriptorOffset);

	GetCommandList()->SetGraphicsRootDescriptorTable(1, DesHandle);
}

void RGeometryMap::DrawMesh()
{
	for (auto& Tmp : m_Geometrys)
	{
		D3D12_VERTEX_BUFFER_VIEW VBV = Tmp.second.GetVertexBufferView();
		D3D12_INDEX_BUFFER_VIEW IBV = Tmp.second.GetIndexBufferView();

		for (int i = 0; i < Tmp.second.m_RenderDatas.size(); i++)
		{
			GetCommandList()->IASetIndexBuffer(&IBV);

			//绑定渲染流水线上的输入槽，可以在输入装配器阶段传入顶点数据
			GetCommandList()->IASetVertexBuffers(
				0,//起始输入槽 0-15 
				1,//k k+1 ... k+n-1 
				&VBV);

			RRenderData& pRenderData = Tmp.second.m_RenderDatas[i];

			//定义我们要绘制的哪种图元 点 线 面
			EMaterialDisplayStatue pDisplayState = (*pRenderData.Mesh->GetMaterials())[0]->GetMaterialDisplayState();
			GetCommandList()->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)pDisplayState);

			auto DesMeshHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
			DesMeshHandle.Offset(i, m_DescriptorOffset);
			GetCommandList()->SetGraphicsRootDescriptorTable(0, DesMeshHandle);
			
			auto DesMaterialHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
			DesMaterialHandle.Offset(i+GetMeshNumber(), m_DescriptorOffset);
			GetCommandList()->SetGraphicsRootDescriptorTable(2, DesMaterialHandle);


			GetCommandList()->DrawIndexedInstanced(
				pRenderData.IndexSize,//顶点数量
				1,//绘制实例数量
				pRenderData.IndexOffsetPosition,//顶点缓冲区第一个被绘制的索引
				pRenderData.VertexOffsetPosition,//GPU 从索引缓冲区读取的第一个索引的位置。
				0);//在从顶点缓冲区读取每个实例数据之前添加到每个索引的值。
		}
	} 
}

void RGeometryMap::UpdateCalculations(const ViewportInfo viewportInfo)
{
	XMMATRIX ViewMatrix = XMLoadFloat4x4(&viewportInfo.ViewMatrix);
	XMMATRIX ProjectMatrix = XMLoadFloat4x4(&viewportInfo.ProjectMatrix);

	for (auto& Tmp : m_Geometrys)//暂时先这么写
	{
		for (size_t i = 0; i < Tmp.second.GetDrawObjectNumber(); i++)
		{
			RRenderData& pRenderData = Tmp.second.m_RenderDatas[i];

			//构造模型的world
			{
				XMFLOAT3& Position = pRenderData.Mesh->GetPosition();
				fvector_3d Scale = pRenderData.Mesh->GetScale();

				XMFLOAT3 RightVector = pRenderData.Mesh->GetRightVector();
				XMFLOAT3 UPVector = pRenderData.Mesh->GetUPVector();
				XMFLOAT3 ForwardVector = pRenderData.Mesh->GetForwardVector();

				pRenderData.WorldMatrix = {
					RightVector.x * Scale.x,	UPVector.x,				ForwardVector.x ,			0.f,
					RightVector.y,				UPVector.y * Scale.y,	ForwardVector.y,			0.f,
					RightVector.z,				UPVector.z ,			ForwardVector.z * Scale.z,	0.f,
					Position.x,					Position.y,				Position.z,					1.f };
			}

			//更新模型位置
			XMMATRIX ATRIXWorld = XMLoadFloat4x4(&pRenderData.WorldMatrix);

			RObjectTransformation ObjectTransformation;
			XMStoreFloat4x4(&ObjectTransformation.World, XMMatrixTranspose(ATRIXWorld));
			m_ObjectConstantBufferView.Update(i, &ObjectTransformation);

			RMaterialConstantBuffer MaterialConstantBuffer;
			{
				if (RMaterial* material = (*pRenderData.Mesh->GetMaterials())[0]) 
				{
					//BaseColor
					fvector_4d pBaseColor = material->GetBaseColor();
					MaterialConstantBuffer.BaseColor = XMFLOAT4(pBaseColor.x, pBaseColor.y, pBaseColor.z, pBaseColor.w);

					//类型输入
					MaterialConstantBuffer.MaterialType = material->GetMaterialType();
					MaterialConstantBuffer.Roughness = material->GetRoughness();
				}

			}
			m_MaterialsBufferView.Update(i, &MaterialConstantBuffer);

		}
	}

	RLightConstantBuffer LightConstantBuffer;
	{

	}
	m_LightsBufferView.Update(0, &LightConstantBuffer);


	//更新视口
	XMMATRIX ViewProject = XMMatrixMultiply(ViewMatrix, ProjectMatrix);
	ViewportTransformation ViewportTransformation;
	XMStoreFloat4x4(&ViewportTransformation.ViewProjectionMatrix, XMMatrixTranspose(ViewProject));
	ViewportTransformation.ViewportPosition = viewportInfo.ViewportPosition;

	m_ViewportConstantBufferView.Update(0, &ViewportTransformation);
}

void RGeometryMap::BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData)
{
	RGeometry& Geometry = m_Geometrys[0];

	Geometry.BuildMesh(mesh, meshData);
}

void RGeometryMap::BuildGeometry() 
{
	for (auto& Tmp : m_Geometrys)
	{
		Tmp.second.Build();
	}
}


bool RGeometry::RenderDataExistence(RMeshComponent* key)
{
	for (auto& Tmp : m_RenderDatas)
	{
		if (Tmp.Mesh == key)
		{
			return true;
		}
	}

	return false;
}

void RGeometry::BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData)
{
	if (!RenderDataExistence(mesh))
	{
		m_RenderDatas.push_back(RRenderData());
		RRenderData& pRenderingData = m_RenderDatas.back();

		pRenderingData.Mesh = mesh;

		pRenderingData.IndexSize = meshData.IndexData.size();
		pRenderingData.VertexSize = meshData.VertexData.size();

		pRenderingData.IndexOffsetPosition = m_MeshRenderData.IndexData.size();
		pRenderingData.VertexOffsetPosition = m_MeshRenderData.VertexData.size();

		m_MeshRenderData.IndexData.insert(
			m_MeshRenderData.IndexData.end(),
			meshData.IndexData.begin(),
			meshData.IndexData.end()); 

		m_MeshRenderData.VertexData.insert(
			m_MeshRenderData.VertexData.end(),
			meshData.VertexData.begin(),
			meshData.VertexData.end());
	}
}

void RGeometry::Build()
{
	UINT VertexSizeInBytes = m_MeshRenderData.GetVertexSizeInBytes();
	UINT IndexSizeInBytes = m_MeshRenderData.GetIndexSizeInBytes();

	ANALYSIS_HRESULT(D3DCreateBlob(VertexSizeInBytes, &CPUVertexBufferPtr));
	memcpy(CPUVertexBufferPtr->GetBufferPointer(), m_MeshRenderData.VertexData.data(), VertexSizeInBytes);

	ANALYSIS_HRESULT(D3DCreateBlob(IndexSizeInBytes, &CPUIndexBufferPtr));
	memcpy(CPUIndexBufferPtr->GetBufferPointer(), m_MeshRenderData.IndexData.data(), IndexSizeInBytes);

	ConstructBuffer::RConstructBuffer pConstructBuffer;

	GPUVertexBufferPtr = pConstructBuffer.ConstructDefaultBuffer(VertexBufferTmpPtr,
		m_MeshRenderData.VertexData.data(), VertexSizeInBytes);

	GPUIndexBufferPtr = pConstructBuffer.ConstructDefaultBuffer(IndexBufferTmpPtr,
		m_MeshRenderData.IndexData.data(), IndexSizeInBytes);
}

D3D12_VERTEX_BUFFER_VIEW RGeometry::GetVertexBufferView()
{
	D3D12_VERTEX_BUFFER_VIEW VBV;
	VBV.BufferLocation = GPUVertexBufferPtr->GetGPUVirtualAddress();
	VBV.SizeInBytes =m_MeshRenderData.GetVertexSizeInBytes();
	VBV.StrideInBytes = sizeof(RVertex);

	return VBV;
}

D3D12_INDEX_BUFFER_VIEW RGeometry::GetIndexBufferView()
{
	D3D12_INDEX_BUFFER_VIEW IBV;
	IBV.BufferLocation = GPUIndexBufferPtr->GetGPUVirtualAddress();
	IBV.SizeInBytes = m_MeshRenderData.GetIndexSizeInBytes();
	IBV.Format = DXGI_FORMAT_R16_UINT;

	return IBV;
}