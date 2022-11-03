#include"ParallelLightComponent.h"
#include"../../Mesh/Base/MeshManage.h"
#include"../Mesh/Core/MeshComponent.h"
#include"../../Mesh/Materials/Material.h"
RParallelLightComponent::RParallelLightComponent()
{
	SetLightMesh( GetMeshManage()->CreateSphereMeshComponent(2.f, 50, 50));
	if (GetLightMesh())
	{
		if (RMaterial* pMaterial = (*GetLightMesh()->GetMaterials())[0])
		{
			pMaterial->SetMaterialType(EMaterialType::BaseColor);
			pMaterial->SetMaterialDisplayState(EMaterialDisplayStatue::RTOPOLOGY_LINELIST);
			pMaterial->SetBaseColor(fvector_4d(1.0f,0.7f,1.0f,1.0f));
		}
	}
}
