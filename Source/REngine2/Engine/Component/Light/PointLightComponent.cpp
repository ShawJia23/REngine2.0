#include"PointLightComponent.h"
#include"../../Manage/MeshManage.h"
#include"../../Materials/Material.h"
#include"../Mesh/MeshComponent.h"

RPointLightComponent::RPointLightComponent() :
	StartAttenuation(1.0f),
	EndAttenuation(1.0f)
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "PointLight";
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(param, 2.f, 50, 50));
	if (GetLightMesh())
	{
		if (RMaterial* pMaterial = (*GetLightMesh()->GetMaterials())[0])
		{
			pMaterial->SetMaterialType(EMaterialType::BaseColor);
			pMaterial->SetMaterialDisplayState(EMaterialDisplayStatue::RTOPOLOGY_LINELIST);
			pMaterial->SetBaseColor(fvector_4d(1.0f, 0.7f, 1.0f, 1.0f));
		}
	}
	LightType = ELightType::PointLight;
}
