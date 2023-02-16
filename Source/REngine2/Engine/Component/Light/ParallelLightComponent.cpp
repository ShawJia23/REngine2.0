#include"ParallelLightComponent.h"
#include"../../Manage/MeshManage.h"
#include"../../Materials/Material.h"
#include"../Mesh/MeshComponent.h"

RParallelLightComponent::RParallelLightComponent()
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "ParallelLight";
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(param, 2.f, 50, 50));
	if (GetLightMesh())
	{
		if (RMaterial* pMaterial = (*GetLightMesh()->GetMaterials())[0])
		{
			pMaterial->SetMaterialType(EMaterialType::BaseColor);
			pMaterial->SetMaterialDisplayState(EMaterialDisplayStatue::RTOPOLOGY_LINELIST);
			pMaterial->SetBaseColor(fvector_4d(0.9f, 0.36f, 0.09f, 1.0f));
		}
	}
}