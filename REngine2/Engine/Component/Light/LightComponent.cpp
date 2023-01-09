#include"LightComponent.h"
#include"../../Manage/LightManage.h"
#include"../Mesh/MeshComponent.h"
#include"../../Manage/MeshManage.h"
#include"../../Materials/Material.h"

#pragma region RLightComponent

RLightComponent::RLightComponent()
	:LightIntensity(1.f, 1.f, 1.f)
{
	GetLightManage()->AddLight(this);
}

RLightComponent::~RLightComponent()
{

}

void RLightComponent::SetLightMesh(RMeshComponent* mesh)
{
	LightMesh = mesh;
}

void RLightComponent::SetPosition(const XMFLOAT3& newPosition)
{
	Super::SetPosition(newPosition);

	LightMesh->SetPosition(newPosition);
}

void RLightComponent::SetForwardVector(const XMFLOAT3& forwardVector)
{
	Super::SetForwardVector(forwardVector);

	if (LightMesh)
	{
		LightMesh->SetForwardVector(forwardVector);
	}
}

void RLightComponent::SetRightVector(const XMFLOAT3& rightVector)
{
	Super::SetRightVector(rightVector);

	LightMesh->SetRightVector(rightVector);
}

void RLightComponent::SetUPVector(const XMFLOAT3& upVector)
{
	Super::SetUPVector(upVector);

	LightMesh->SetUPVector(upVector);
}

void RLightComponent::SetRotation(const fvector_3d& InNewRotation)
{
	Super::SetRotation(InNewRotation);

	LightMesh->SetRotation(InNewRotation * (-1));
}

void RLightComponent::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	LightMesh->SetScale(InNewScale);
}

#pragma endregion

#pragma region Parallel

RParallelLightComponent::RParallelLightComponent()
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(param,2.f, 50, 50));
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

#pragma endregion

#pragma region Point

RPointLightComponent::RPointLightComponent() :
	StartAttenuation(1.0f),
	EndAttenuation(1.0f)
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(param,2.f, 50, 50));
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

#pragma endregion

#pragma region Spot

RSpotLightComponent::RSpotLightComponent()
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightMesh(GetMeshManage()->CreateSphereMeshComponent(param,2.f, 50, 50));
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

#pragma endregion

