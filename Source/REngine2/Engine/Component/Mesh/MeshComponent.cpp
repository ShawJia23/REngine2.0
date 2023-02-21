#include"MeshComponent.h"
#include"../../Mesh/MeshType.h"

RMeshComponent::RMeshComponent():
	MeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE),
	bVisible(true)
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "Material";
	m_Materials.push_back(CreateObject<RMaterial>(param,new RMaterial()));
}

void RMeshComponent::Init()
{

}

void RMeshComponent::BuildMesh(const MeshRenderData* InRenderingData)
{

}
