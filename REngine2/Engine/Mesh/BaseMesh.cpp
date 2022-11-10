#include "BaseMesh.h"
#include"../LoadAsset/Texture.h"
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
void  BoxMesh::CreateMesh(float height, float width, float depth)
{
	auto Tmp = CREATE_RENDER_DATA(BoxMeshComponent, height, width, depth);
	SetMeshComponent(Tmp);
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

void ConeMesh::CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub)
{
	auto Tmp = CREATE_RENDER_DATA(ConeMeshComponent, radius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
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

void CylinderMesh::CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub)
{
	auto Tmp = CREATE_RENDER_DATA(CylinderMeshComponent, topRadius, bottomRadius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
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

void PlaneMesh::CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub)
{
	auto Tmp = CREATE_RENDER_DATA(PlaneMeshComponent, height, width, heightSub, widthSub);
	SetMeshComponent(Tmp);
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

void SphereMesh::CreateMesh( float radius, uint32_t axialSub, uint32_t heightSub) 
{
	auto Tmp = CREATE_RENDER_DATA(SphereMeshComponent, radius, axialSub, heightSub);
	SetMeshComponent(Tmp);
	
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

void CustomMesh::CreateMesh()
{
	auto Tmp = CREATE_RENDER_DATA(CustomMeshComponent, 0);
	SetMeshComponent(Tmp);
}

MeshGroup::MeshGroup()
{
	m_RenderDatas.clear();
}

void MeshGroup::AddSubmesh(std::string name, RMeshComponent* mesh, MeshRenderData MeshData)
{
	CustomMesh* pCustomMesh=GetWorld()->CreateActorObject<CustomMesh>();
	if (pCustomMesh)
	{
		pCustomMesh->SetMeshComponent(mesh);
		pCustomMesh->SetPosition(XMFLOAT3(0.f, -2.f, 15.f));
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

void MeshGroup::AddTexture(std::string objName,std::string texName, std::string fileName)
{
	GetTextureManage()->LoadTextureFormPath(texName, fileName);

	if (m_RenderDatas.find(objName) != m_RenderDatas.end())
	{
		auto Tmp = m_RenderDatas[objName].Mesh;
		if (RMaterial* pMaterial = (*Tmp->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetBaseColorIndexKey(texName);
			pMaterial->SetMaterialType(EMaterialType::Lambert);
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
