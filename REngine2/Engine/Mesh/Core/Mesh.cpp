#include "Mesh.h"
#include"../../Config/RenderConfig.h"
#include"../../Render/ResourcesUpdate.h"
#include"../../Component/Mesh/Core/MeshComponent.h"
#include"../../Materials/Material.h"
BMesh::BMesh():GActorObject()
{
}

void BMesh::Init()
{

}

void BMesh::PreDraw(float DeltaTime)
{
}

void BMesh::Draw(float DeltaTime)
{
}

void BMesh::PostDraw(float DeltaTime)
{
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

	//��Ϊ��δ�����������ʱ��ôд
	GetMeshComponent()->SetPosition(InNewPosition);
}

void BMesh::SetRotation(const fvector_3d& InRotation)
{
	Super::SetRotation(InRotation);

	//��Ϊ��δ�����������ʱ��ôд
	GetMeshComponent()->SetRotation(InRotation);
}

void BMesh::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	//��Ϊ��δ�����������ʱ��ôд
	GetMeshComponent()->SetScale(InNewScale);
}