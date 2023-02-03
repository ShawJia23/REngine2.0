#include "Mesh.h"
#include"../Manage/TextureManage.h"
#include"../Core/World.h"
#include"../Materials/Material.h"
#include"../Component/Mesh/BaseMeshComponent.h"
#include"../Core/Construction/MacroConstruction.h"
BoxMesh::BoxMesh() 
{
	Rename("Box");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "BoxComponent";
	auto Tmp = CREATE_RENDER_DATA(BoxMeshComponent,height, width, depth);
	SetMeshComponent(Tmp);
}

ConeMesh::ConeMesh()
{
	Rename("Cone");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "ConeComponent";
	auto Tmp = CREATE_RENDER_DATA(ConeMeshComponent, radius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

CylinderMesh::CylinderMesh()
{
	Rename("Cylinder");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "CylinderComponent";
	auto Tmp = CREATE_RENDER_DATA(CylinderMeshComponent, topRadius, bottomRadius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

PlaneMesh::PlaneMesh()
{
	Rename("Plane");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "PlaneComponent";
	auto Tmp = CREATE_RENDER_DATA(PlaneMeshComponent, height, width, heightSub, widthSub);
	SetMeshComponent(Tmp);
}

SphereMesh::SphereMesh()
{
	Rename("Sphere");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "SphereComponent";
	auto Tmp = CREATE_RENDER_DATA(SphereMeshComponent, radius, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

CustomMesh::CustomMesh()
{
	Rename("Custom");
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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "CustomComponent";
	auto Tmp = CREATE_RENDER_DATA(CustomMeshComponent, "name");
	SetMeshComponent(Tmp);
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
	if (m_RenderDatas.find(name) != m_RenderDatas.end())
	{
		name = name + "1";
	}
	size_t hashKey = 0;
	dynamic_cast<CustomMeshComponent*>(mesh)->BuildKey(hashKey, name);
	CustomMesh* pCustomMesh=GetWorld()->CreateActorObject<CustomMesh>();
	if (pCustomMesh)
	{
		mesh->Rename("CustomComponent");
		mesh->SetOuter(pCustomMesh);
		pCustomMesh->SetMeshComponent(mesh);
		pCustomMesh->Rename(name);
	}
	SubMesh pSubMesh;
	pSubMesh.Mesh = pCustomMesh;
	pSubMesh.MeshData.IndexData = MeshData.IndexData;
	pSubMesh.MeshData.VertexData = MeshData.VertexData;
	pSubMesh.outKey = hashKey;
	m_RenderDatas[name] = pSubMesh;
}

void MeshGroup::CreateMesh()
{
	for (auto Tmp :m_RenderDatas) 
	{
		GetMeshManage()->CreateMeshGroup(Tmp.second.outKey,Tmp.second.Mesh->GetMeshComponent(), Tmp.second.MeshData);
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
