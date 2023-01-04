#include "Mesh.h"
#include"../Manage/TextureManage.h"
#include"../Core/World.h"
#include"../Materials/Material.h"
#include"../Component/Mesh/BaseMeshComponent.h"

BoxMesh::BoxMesh() 
{
}
void BoxMesh::Init()
{
	Super::Init();
}
void BoxMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}
void  BoxMesh::CreateMesh(float height, float width, float depth, EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(BoxMeshComponent,height, width, depth);
	SetMeshComponent(Tmp);
}

void BoxMesh::BuildKey(size_t& outKey, float height, float width, float depth) 
{
	std::hash<float> floatHash;

	outKey = 1;
	outKey += floatHash(height);
	outKey += floatHash(width);
	outKey += floatHash(depth);
}

ConeMesh::ConeMesh()
{
}

void ConeMesh::Init()
{
	Super::Init();
}

void ConeMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void ConeMesh::CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(ConeMeshComponent, radius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

void ConeMesh::BuildKey(size_t& outKey, float radius, float height, uint32_t axialSub, uint32_t heightSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 2;
	outKey += floatHash(radius);
	outKey += floatHash(height);

	outKey += intHash(axialSub);
	outKey += intHash(heightSub);
}

CylinderMesh::CylinderMesh()
{
}

void CylinderMesh::Init()
{
	Super::Init();
}

void CylinderMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void CylinderMesh::CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(CylinderMeshComponent, topRadius, bottomRadius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

void CylinderMesh::BuildKey(size_t& outKey, float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 3;
	outKey += floatHash(topRadius);
	outKey += floatHash(bottomRadius);
	outKey += floatHash(height);
	outKey += intHash(axialSub);
	outKey += intHash(heightSub);
}

PlaneMesh::PlaneMesh()
{
}

void PlaneMesh::Init()
{
	Super::Init();
}

void PlaneMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void PlaneMesh::CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub, EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(PlaneMeshComponent, height, width, heightSub, widthSub);
	SetMeshComponent(Tmp);
}

void PlaneMesh::BuildKey(size_t& outKey, float height, float width, uint32_t heightSub, uint32_t widthSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 4;
	outKey += floatHash(height);
	outKey += floatHash(width);
	outKey += intHash(heightSub);
	outKey += intHash(widthSub);
}

SphereMesh::SphereMesh()
{
}

void SphereMesh::Init()
{
	Super::Init();
}

void SphereMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void SphereMesh::CreateMesh( float radius, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(SphereMeshComponent, radius, axialSub, heightSub);

	SetMeshComponent(Tmp);
	
}

void SphereMesh::BuildKey(size_t& outKey, float radius, uint32_t axialSub, uint32_t heightSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;

	outKey = 5;
	outKey += floatHash(radius);

	outKey += intHash._Do_hash(axialSub);
	outKey += intHash._Do_hash(heightSub);
}

CustomMesh::CustomMesh()
{
}

void CustomMesh::Init()
{
	Super::Init();
}

void CustomMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void CustomMesh::CreateMesh(EMeshRenderLayerType type)
{
	auto Tmp = CREATE_RENDER_DATA(CustomMeshComponent,0);
	SetMeshComponent(Tmp);
}

void CustomMesh::BuildKey(size_t& outKey)
{
	std::hash<float> floatHash;

	outKey = 5;
}

MeshGroup::MeshGroup()
{
	m_RenderDatas.clear();
}

void MeshGroup::SetPosition(const XMFLOAT3& newPosition) 
{
	for (auto& Tmp : m_RenderDatas)
	{
		Tmp.second.Mesh->SetPosition(newPosition);
	}
}

void MeshGroup::AddSubmesh(std::string name, RMeshComponent* mesh, MeshRenderData MeshData)
{
	CustomMesh* pCustomMesh=GetWorld()->CreateActorObject<CustomMesh>();
	if (pCustomMesh)
	{
		pCustomMesh->SetMeshComponent(mesh);
	}
	SubMesh pSubMesh;
	pSubMesh.Mesh = pCustomMesh;
	pSubMesh.MeshData.IndexData = MeshData.IndexData;
	pSubMesh.MeshData.VertexData = MeshData.VertexData;
	if (m_RenderDatas.find(name) != m_RenderDatas.end()) 
	{
		name = name + "1";
	}
	m_RenderDatas[name] = pSubMesh;
}

void MeshGroup::CreateMesh()
{
	for (auto Tmp :m_RenderDatas) 
	{
		GetMeshManage()->CreateMeshGroup(Tmp.second.Mesh->GetMeshComponent(), Tmp.second.MeshData);
	}
}

void MeshGroup::AddTexture(std::string objName, std::string texName, std::string fileName, int type) 
{
	if (texName.empty() || fileName.empty())
		return;
	GetTextureManage()->LoadTextureFormPath(texName, fileName);

	if (m_RenderDatas.find(objName) != m_RenderDatas.end())
	{
		auto Tmp = m_RenderDatas[objName].Mesh;
		if (RMaterial* pMaterial = (*Tmp->GetMaterials())[0])
		{
			switch (type)
			{
			case 1:
				pMaterial->SetBaseColorIndexKey(texName);
				break;
			case 2:
				pMaterial->SetSpecularIndexKey(texName);
				break;
			case 6:
				pMaterial->SetNormalIndexKey(texName);
				break;
			default:
				break;
			}
			pMaterial->SetRoughness(0.8f);
		}
	}
}
void MeshGroup::CreateTexture()
{
	GetTextureManage()->CreateTexture();
}

MeshGroup::SubMesh::SubMesh():
	Mesh(NULL)
{
}
