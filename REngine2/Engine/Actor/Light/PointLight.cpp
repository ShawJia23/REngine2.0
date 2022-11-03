#include"PointLight.h"
#include"../../Component/Light/PointLightComponent.h"

GPointLight::GPointLight()
{
	SetLightComponent(CreateObject<RPointLightComponent>(new RPointLightComponent()));
}

void GPointLight::Tick(float DeltaTime)
{
	fvector_3d v3 = GetRotation();

	v3.x += DeltaTime * 10.f;
	v3.y += DeltaTime * 10.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}


float GPointLight::GetStartAttenuation() const
{
	if (const RPointLightComponent* pLightComponent = dynamic_cast<const RPointLightComponent*>(GetLightComponent()))
	{
		return pLightComponent->GetStartAttenuation();
	}

	return 0.f;
}

float GPointLight::GetEndAttenuation() const
{
	if (const RPointLightComponent* pLightComponent = dynamic_cast<const RPointLightComponent*>(GetLightComponent()))
	{
		return pLightComponent->GetEndAttenuation();
	}

	return 0.f;
}

void GPointLight::SetStartAttenuation(float InNewStartAttenuation)
{
	if (RPointLightComponent* pLightComponent = dynamic_cast<RPointLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetStartAttenuation(InNewStartAttenuation);
	}
}

void GPointLight::SetEndAttenuation(float InNewEndAttenuation)
{
	if (RPointLightComponent* pLightComponent = dynamic_cast<RPointLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetEndAttenuation(InNewEndAttenuation);
	}
}