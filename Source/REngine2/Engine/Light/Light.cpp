#include "Light.h"
#include"../Component/Light/LightComponent.h"
#include"Construction/ObjectConstruction.h"

GLight::GLight()
	:Super()
	, LightComponent(NULL)
{

}

void GLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void GLight::SetPosition(const XMFLOAT3& InNewPosition)
{
	Super::SetPosition(InNewPosition);

	if (LightComponent)
	{
		LightComponent->SetPosition(InNewPosition);
	}
}

void GLight::SetRotation(const fvector_3d& InRotation)
{
	Super::SetRotation(InRotation);

	if (LightComponent)
	{
		LightComponent->SetRotation(InRotation);
	}
}

void GLight::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	if (LightComponent)
	{
		LightComponent->SetScale(InNewScale);
	}
}

void GLight::SetLightIntensity(const fvector_3d& InNewLightIntensity)
{
	if (LightComponent)
	{
		LightComponent->SetLightIntensity(InNewLightIntensity);
	}
}

void GLight::SetLightComponent(RLightComponent* InNewComponent)
{
	LightComponent = InNewComponent;
}