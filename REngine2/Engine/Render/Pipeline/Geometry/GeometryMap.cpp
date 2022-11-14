#include"GeometryMap.h"
#include"../../Buffer/ConstructBuffer.h"
#include"../../../Mesh/Mesh.h"
#include"../../../Materials/Material.h"
#include"../../../Manage/LightManage.h"
#include"../../../LoadAsset/Texture.h"
#include"../../../Component/RComponentMinimal.h"
#include"../../ConstontBuffer/ConstontBufferMinimal.h"
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

	//收集材质
	//正真更新Shader-Index
	for (auto& Tmp : m_Geometrys)
	{
		for (size_t i = 0; i < Tmp.second.m_RenderDatas.size(); i++)
		{
			auto& InData = Tmp.second.m_RenderDatas[i];
			if (auto InMaterials = InData.Mesh->GetMaterials())
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

UINT RGeometryMap::GetTextureNumber()
{
	return GetTextureManage()->GetTextureSize();
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
			XMMATRIX ATRIXTextureTransform = XMLoadFloat4x4(&pRenderData.TextureTransform);

			RObjectTransformation ObjectTransformation;
			XMStoreFloat4x4(&ObjectTransformation.World, XMMatrixTranspose(ATRIXWorld));
			XMStoreFloat4x4(&ObjectTransformation.TextureTransformation, XMMatrixTranspose(ATRIXTextureTransform));
			//收集材质Index
			if (auto& InMater = (*pRenderData.Mesh->GetMaterials())[0])
			{
				ObjectTransformation.MaterialIndex = InMater->GetMaterialIndex();
			}

			m_ObjectConstantBufferView.Update(i, &ObjectTransformation);

		}
	}

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
	XMMATRIX ViewProject = XMMatrixMultiply(ViewMatrix, ProjectMatrix);
	ViewportTransformation ViewportTransformation;
	XMStoreFloat4x4(&ViewportTransformation.ViewProjectionMatrix, XMMatrixTranspose(ViewProject));
	ViewportTransformation.ViewportPosition = viewportInfo.ViewportPosition;

	m_ViewportConstantBufferView.Update(0, &ViewportTransformation);
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
				XMStoreFloat4x4(&MaterialConstantBuffer.TransformInformation,
					XMMatrixTranspose(MaterialTransform));

				InMaterial->SetDirty(false);

				m_MaterialsBufferView.Update(InMaterial->GetMaterialIndex(), &MaterialConstantBuffer);
			}
		}
	}
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