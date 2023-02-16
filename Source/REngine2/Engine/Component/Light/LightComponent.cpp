#include"LightComponent.h"
#include"../../Manage/LightManage.h"
#include"../Mesh/MeshComponent.h"
#include"../../Manage/MeshManage.h"
#include"../../Materials/Material.h"

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
