#include"GeometryMap.h"
#include"../../Buffer/ConstructBuffer.h"
#include"../../../Mesh/Mesh.h"
#include"../../../Materials/Material.h"
#include"../../../Manage/LightManage.h"
#include"../../../LoadAsset/Texture.h"
#include"../../../Component/RComponentMinimal.h"
#include"../../ConstontBuffer/ConstontBufferMinimal.h"
#include"../RenderLayer/RenderLayerManage.h"

UINT MeshObjectCount=0;

RGeometryMap::RGeometryMap()
:m_WorldMatrix(RMath::IdentityMatrix4x4())
, IndexSize(0)
{
	m_Geometrys.insert(pair<int, RGeometry*>(0, new RGeometry()));
	m_RenderLayerManage = std::make_unique<RenderLayerManage>();
}

void RGeometryMap::Init() 
{
	m_DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	
}

void RGeometryMap::BuildDescriptorHeap()
{
	m_DescriptorHeap.CreatePSO(GetMeshNumber() + GetMaterialsNumber() + GetLightsNumber() + 1);
}

void RGeometryMap::BuildConstantBufferView()
{
	BuildMeshConstantBufferView();
	BuildMaterialsConstantBufferView();
	BuildLightsConstantBufferView();
	BuildViewportConstantBufferView();
	BuildTextureConstantBuffer();
}

void RGeometryMap::BuildMeshConstantBufferView()
{
	m_ObjectConstantBufferView.CreateConstant(sizeof(RObjectTransformation), GetMeshNumber());

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_ObjectConstantBufferView.BuildConstantBuffer(DesHandle, GetMeshNumber());
}

void RGeometryMap::BuildMaterialsConstantBufferView()
{
	//创建常量缓冲区
	m_MaterialsBufferView.CreateConstant(
		sizeof(RMaterialConstantBuffer),
		GetMaterialsNumber(),
		false);

	for (auto& Tmp : m_RenderLayerManage->GetAllRenderLayers())
	{
		for (size_t i = 0; i < Tmp.second->GetRenderDataSize(); i++)
		{
			auto RenderDatas = Tmp.second->GetRenderDatas();
			auto InData = RenderDatas[i];
			if (auto InMaterials = InData->Mesh->GetMaterials())
			{
				for (size_t j = 0; j < InMaterials->size(); j++)
				{
					//做ShaderIndex所有
					(*InMaterials)[j]->SetMaterialIndex(Materials.size());

					Materials.push_back((*InMaterials)[j]);
				}
			}
		}
	}
}

void RGeometryMap::BuildLightsConstantBufferView()
{
	m_LightsBufferView.CreateConstant(sizeof(RLightConstantBuffer), 1);

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_LightsBufferView.BuildConstantBuffer(DesHandle, GetLightsNumber(), GetMeshNumber());
}

void RGeometryMap::BuildViewportConstantBufferView()
{
	m_ViewportConstantBufferView.CreateConstant(sizeof(ViewportTransformation), 1);

	CD3DX12_CPU_DESCRIPTOR_HANDLE DesHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(GetHeap()->GetCPUDescriptorHandleForHeapStart());

	m_ViewportConstantBufferView.BuildConstantBuffer(DesHandle, 1, GetMeshNumber()+GetLightsNumber());
}

void RGeometryMap::BuildTextureConstantBuffer() 
{
	GetTextureManage()->BuildTextureConstantBuffer(
		m_DescriptorHeap.GetHeap(),
		GetMeshNumber()  + GetLightsNumber()+1);//视口
}


UINT RGeometryMap::GetMeshNumber()
{
	int count = 0;
	for (auto& Tmp : m_RenderLayerManage->GetAllRenderLayers()) 
	{
		count += Tmp.second->GetRenderDataSize();
	}
	return count;
}

UINT RGeometryMap::GetMaterialsNumber()
{
	UINT pMatereials = 0;
	for (auto& Tmp : m_RenderLayerManage->GetAllRenderLayers())
	{
		for (size_t i = 0; i < Tmp.second->GetRenderDataSize(); i++)
		{
			auto RenderDatas = Tmp.second->GetRenderDatas();
			auto InData = RenderDatas[i];
			if (auto InMaterials = InData->Mesh->GetMaterials())
			{
				for (size_t j = 0; j < InMaterials->size(); j++)
				{
					pMatereials++;
				}
			}
		}
	}
	return pMatereials;
}

UINT RGeometryMap::GetLightsNumber()
{
	return 1;
}

UINT RGeometryMap::GetTextureNumber()
{
	return GetTextureManage()->GetTextureSize();
}


void RGeometryMap::SetPipelineState(RDXPipelineState* pipelineState)
{
	m_RenderLayerManage->SetPipelineState(pipelineState);
}

void RGeometryMap::BuildPSO()
{
	m_RenderLayerManage->BuildPSO(GetTextureManage()->GetTextureSize());
}

void RGeometryMap::Draw() 
{
	DrawViewport();
	DrawLights();
	DrawTexture();
	DrawMaterial();
	DrawMesh();
}

void RGeometryMap::DrawMaterial()
{
	GetCommandList()->SetGraphicsRootShaderResourceView(
		4,
		m_MaterialsBufferView.GetBuffer()->GetGPUVirtualAddress());
}

void RGeometryMap::DrawLights()
{
	auto DesHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
	DesHandle.Offset(GetMeshNumber(), m_DescriptorOffset);

	GetCommandList()->SetGraphicsRootDescriptorTable(2, DesHandle);
}

void RGeometryMap::DrawViewport()
{
	m_DescriptorHeap.SetDescriptorHeap();

	auto DesHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
	DesHandle.Offset(GetMeshNumber()+GetLightsNumber(), m_DescriptorOffset);

	GetCommandList()->SetGraphicsRootDescriptorTable(1, DesHandle);
}

void RGeometryMap::DrawTexture()
{
	auto DesHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(GetHeap()->GetGPUDescriptorHandleForHeapStart());
	DesHandle.Offset(GetMeshNumber() + GetLightsNumber() + 1, m_DescriptorOffset);

	GetCommandList()->SetGraphicsRootDescriptorTable(3, DesHandle);
}

void RGeometryMap::DrawMesh()
{
	m_RenderLayerManage->DrawMesh(m_Geometrys, GetHeap());
}


void RGeometryMap::UpdateCalculations(const ViewportInfo viewportInfo)
{
	m_RenderLayerManage->UpdateCalculations(viewportInfo, m_ObjectConstantBufferView);

	UpdateMaterialShaderResourceView();
	
	RLightConstantBuffer LightConstantBuffer;
	for (size_t i = 0; i < GetLightManage()->Lights.size(); i++)
	{
		if (RLightComponent* pLight = GetLightManage()->Lights[i])
		{
			fvector_3d LightIntensity = pLight->GetLightIntensity();
			LightConstantBuffer.SceneLights[i].LightIntensity = XMFLOAT3(LightIntensity.x, LightIntensity.y, LightIntensity.z);
			LightConstantBuffer.SceneLights[i].LightDirection = pLight->GetForwardVector();
			LightConstantBuffer.SceneLights[i].Position = pLight->GetPosition();
			LightConstantBuffer.SceneLights[i].LightType = pLight->GetLightType();
			switch (pLight->GetLightType())
			{
			case ELightType::PointLight: 
			{
				if (RPointLightComponent* pPointLight = dynamic_cast<RPointLightComponent*>(pLight))
				{
					LightConstantBuffer.SceneLights[i].StartAttenuation = pPointLight->GetStartAttenuation();
					LightConstantBuffer.SceneLights[i].EndAttenuation = pPointLight->GetEndAttenuation();
				}
			}
			break;
			case ELightType::SpotLight:
			{
				if (RSpotLightComponent* pSpotLight = dynamic_cast<RSpotLightComponent*>(pLight))
				{
					LightConstantBuffer.SceneLights[i].StartAttenuation = pSpotLight->GetStartAttenuation();
					LightConstantBuffer.SceneLights[i].EndAttenuation = pSpotLight->GetEndAttenuation();
					LightConstantBuffer.SceneLights[i].InnerCorner = pSpotLight->GetInnerCorner();
					LightConstantBuffer.SceneLights[i].OuterCorner = pSpotLight->GetOuterCorner();
				}
			}
			break;
			default:
				break;
			}
		}
	}
	m_LightsBufferView.Update(0, &LightConstantBuffer);
	//更新视口

	XMMATRIX ViewMatrix = XMLoadFloat4x4(&viewportInfo.ViewMatrix);
	XMMATRIX ProjectMatrix = XMLoadFloat4x4(&viewportInfo.ProjectMatrix);

	XMMATRIX ViewProject = XMMatrixMultiply(ViewMatrix, ProjectMatrix);

	ViewportTransformation viewTrans;
	DirectX::XMStoreFloat4x4(&viewTrans.ViewProjectionMatrix, XMMatrixTranspose(ViewProject));
	viewTrans.ViewportPosition = viewportInfo.ViewportPosition;

	m_ViewportConstantBufferView.Update(0, &viewTrans);
}

void RGeometryMap::UpdateMaterialShaderResourceView()
{
	RMaterialConstantBuffer MaterialConstantBuffer;
	for (size_t i = 0; i < Materials.size(); i++)
	{
		//变换材质
		if (RMaterial* InMaterial = Materials[i])
		{
			if (InMaterial->IsDirty())
			{
				//BaseColor
				fvector_4d InBaseColor = InMaterial->GetBaseColor();
				MaterialConstantBuffer.BaseColor = XMFLOAT4(InBaseColor.x, InBaseColor.y, InBaseColor.z, InBaseColor.w);

				fvector_3d InSpecularColor = InMaterial->GetSpecularColor();
				MaterialConstantBuffer.SpecularColor = XMFLOAT3(InSpecularColor.x, InSpecularColor.y, InSpecularColor.z);

				//粗糙度
				MaterialConstantBuffer.Roughness = InMaterial->GetRoughness();

				//类型输入
				MaterialConstantBuffer.MaterialType = InMaterial->GetMaterialType();

				MaterialConstantBuffer.BaseColorIndex = GetTextureManage()->FindRenderingTextureIndex(InMaterial->GetBaseColorIndexKey());
				MaterialConstantBuffer.NormalIndex = GetTextureManage()->FindRenderingTextureIndex(InMaterial->GetNormalIndexKey());
				MaterialConstantBuffer.SpecularIndex = GetTextureManage()->FindRenderingTextureIndex(InMaterial->GetSpecularIndexKey());

				//材质矩阵
				XMMATRIX MaterialTransform = XMLoadFloat4x4(&InMaterial->GetMaterialTransform());
				DirectX::XMStoreFloat4x4(&MaterialConstantBuffer.TransformInformation,
					XMMatrixTranspose(MaterialTransform));

				InMaterial->SetDirty(false);

				m_MaterialsBufferView.Update(InMaterial->GetMaterialIndex(), &MaterialConstantBuffer);
			}
		}
	}
}


void RGeometryMap::BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData)
{
	RGeometry* Geometry = m_Geometrys[0];

	auto renderLayer = m_RenderLayerManage->GetRenderLayerByType(mesh->GetRenderLayerType());
	if(renderLayer)
		Geometry->BuildMesh(mesh, meshData, renderLayer);
}

void RGeometryMap::BuildGeometry() 
{
	for (auto& Tmp : m_Geometrys)
	{
		Tmp.second->CreatePSO();
	}
}


bool RGeometry::RenderDataExistence(RMeshComponent* key, std::shared_ptr<RenderLayer> renderLayer)
{
	for (auto& Tmp : renderLayer->GetRenderDatas())
	{
		if (Tmp->Mesh == key)
		{
			return true;
		}
	}

	return false;
}

void RGeometry::BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData, std::shared_ptr<RenderLayer> renderLayer)
{
	if (!RenderDataExistence(mesh, renderLayer))
	{
		RRenderData* pRenderingData = new RRenderData();

		pRenderingData->Mesh = mesh;
		pRenderingData->ObjectIndex = MeshObjectCount++;
		pRenderingData->IndexSize = meshData.IndexData.size();
		pRenderingData->VertexSize = meshData.VertexData.size();

		pRenderingData->IndexOffsetPosition = m_MeshRenderData.IndexData.size();
		pRenderingData->VertexOffsetPosition = m_MeshRenderData.VertexData.size();

		renderLayer->AddRenderData(pRenderingData);

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

void RGeometry::CreatePSO()
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