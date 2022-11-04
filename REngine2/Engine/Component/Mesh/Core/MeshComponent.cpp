#include"MeshComponent.h"
#include"../../../Mesh/Core/MeshType.h"

RMeshComponent::RMeshComponent()
{
	m_Materials.push_back(CreateObject<RMaterial>(new RMaterial()));
}

void RMeshComponent::Init()
{

}

void RMeshComponent::BuildMesh(const MeshRenderData* InRenderingData)
{

}
