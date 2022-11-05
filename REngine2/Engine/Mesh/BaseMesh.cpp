#include "BaseMesh.h"
#include"Core/MeshManage.h"
#include"../Core/World.h"
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
	SetMeshComponent(GetMeshManage()->CreateBoxMeshComponent(height, width, depth));
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
	SetMeshComponent(GetMeshManage()->CreateConeMeshComponent(radius, height, axialSub, heightSub));
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
	SetMeshComponent(GetMeshManage()->CreateCylinderMeshComponent(topRadius, bottomRadius,height,axialSub, heightSub));
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
	SetMeshComponent(GetMeshManage()->CreatePlaneMeshComponent(height, width, heightSub, widthSub));
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
	SetMeshComponent(GetMeshManage()->CreateSphereMeshComponent(radius, axialSub, heightSub));
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
	SetMeshComponent(GetMeshManage()->CreateCustomMeshComponent());
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
	pSubMesh.Mesh = mesh;
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
		GetMeshManage()->CreateMeshGroup(Tmp.second.Mesh, Tmp.second.MeshData);
	}
}

MeshGroup::SubMesh::SubMesh():
	Mesh(NULL)
{
}
