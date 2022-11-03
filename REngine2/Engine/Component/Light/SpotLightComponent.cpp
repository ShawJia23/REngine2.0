#include"SpotLightComponent.h"
#include"../../Mesh/Base/MeshManage.h"
#include"../Mesh/Core/MeshComponent.h"
#include"../../Mesh/Materials/Material.h"
RSpotLightComponent::RSpotLightComponent()
{
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(2.f, 50, 50));
	if (GetLightMesh())
	{
		if (RMaterial* pMaterial = (*GetLightMesh()->GetMaterials())[0])
		{
			pMaterial->SetMaterialType(EMaterialType::BaseColor);
			pMaterial->SetMaterialDisplayState(EMaterialDisplayStatue::RTOPOLOGY_LINELIST);
			pMaterial->SetBaseColor(fvector_4d(1.0f, 0.7f, 1.0f, 1.0f));
		}
	}
	LightType = ELightType::SpotLight;
}


void RSpotLightComponent::SetOuterCorner(float outerCorner)
{
	m_OuterCorner = outerCorner;
	m_InnerCorner = m_OuterCorner > m_InnerCorner ? m_InnerCorner : m_OuterCorner;
}


void RSpotLightComponent::SetInnerCorner(float innerCorner)
{
	m_InnerCorner = innerCorner;
	m_OuterCorner = m_OuterCorner < m_InnerCorner ? m_InnerCorner : m_OuterCorner;
}