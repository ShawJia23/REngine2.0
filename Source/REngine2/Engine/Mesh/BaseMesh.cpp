#include "BaseMesh.h"
#include"../Config/RenderConfig.h"
#include"../Render/ResourcesUpdate.h"
#include"../Component/Mesh/MeshComponent.h"
#include"../Materials/Material.h"
BMesh::BMesh()
{
}

void BMesh::Init()
{

}

void BMesh::PreDraw(GameTimer& gt)
{
}

void BMesh::Draw(GameTimer& gt)
{
}

void BMesh::PostDraw(GameTimer& gt)
{
}

void BMesh::SetPickup(bool bNewPickup)
{
	GetMeshComponent()->SetPickup(bNewPickup);
}


UINT BMesh::GetMaterialsNum()
{
	return MeshComponent->GetMaterialsNum();
}

vector<RMaterial*>* BMesh::GetMaterials()
{ 
	return MeshComponent->GetMaterials();
}


void BMesh::SetPosition(const XMFLOAT3& InNewPosition)
{
	Super::SetPosition(InNewPosition);

	GetMeshComponent()->SetPosition(InNewPosition);
}

void BMesh::SetRotation(const fvector_3d& InRotation)
{
	Super::SetRotation(InRotation);

	GetMeshComponent()->SetRotation(InRotation);
}

void BMesh::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	GetMeshComponent()->SetScale(InNewScale);
}


void BMesh::SetMeshComponent(RMeshComponent* InMeshComponent)
{ 
	MeshComponent = InMeshComponent; 
	MeshComponent->SetOuter(this);
}
void BMesh::SetRenderLayer(EMeshRenderLayerType type)
{
	MeshComponent->SetMeshRenderLayerType(type); 
}

RMeshComponent* BMesh::GetMeshComponent()
{
	return MeshComponent; 
}