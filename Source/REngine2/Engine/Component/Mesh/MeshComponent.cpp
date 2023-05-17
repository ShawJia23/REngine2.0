#include"MeshComponent.h"
#include"../../Mesh/MeshType.h"
#include"../../Construction/MacroConstruction.h"
RMeshComponent::RMeshComponent():
	MeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE),
	bVisible(true),
	bPickup(true),
	bCastShadow(true)
{
	BUILD_OBJECT_PARAMETERS_BY_NO_COMPONENT(this);
	m_Materials.push_back(CreateObject<RMaterial>(inObjectParam,new RMaterial()));
}

void RMeshComponent::Init()
{

}

void RMeshComponent::BuildMesh(const MeshRenderData* InRenderingData)
{

}

bool RMeshComponent::IsDynamicReflection() const
{
	if (m_Materials.size() >= 1)
	{
		return
			m_Materials[0]->IsDynamicReflection();
	}

	return false;
}