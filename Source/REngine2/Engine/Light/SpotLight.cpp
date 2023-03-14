#include"SpotLight.h"
#include"../Component/Light/SpotLightComponent.h"
#include"../Construction/MacroConstruction.h"
float index_test;
GSpotLight::GSpotLight()
{
	BUILD_OBJECT_PARAMETERS(this);
	SetLightComponent(CreateObject<RSpotLightComponent>(inObjectParam, new RSpotLightComponent()));
	index_test = 0;
}

void GSpotLight::Tick(GameTimer& gt)
{
	index_test += gt.DeltaTime();

	float O = 50.f;
	float I = 30.f;

	SetInnerCorner(I * fabsf(cos(index_test)) + 10.f);
	SetOuterCorner(O * fabsf(cos(index_test)) + 20.f);

	fvector_3d v3 = GetRotation();

	v3.x += gt.DeltaTime() * 10.f;
	v3.y += gt.DeltaTime() * 10.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}


float GSpotLight::GetStartAttenuation() const
{
	if (const RSpotLightComponent* pLightComponent = dynamic_cast<const RSpotLightComponent*>(GetLightComponent()))
	{
		return pLightComponent->GetStartAttenuation();
	}

	return 0.f;
}

float GSpotLight::GetEndAttenuation() const
{
	if (const RSpotLightComponent* pLightComponent = dynamic_cast<const RSpotLightComponent*>(GetLightComponent()))
	{
		return pLightComponent->GetEndAttenuation();
	}

	return 0.f;
}

float GSpotLight::GetInnerCorner() const
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->GetInnerCorner();
	}

	return 0.0f;
}

float GSpotLight::GetOuterCorner() const
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->GetOuterCorner();
	}

	return 0.0f;
}


void GSpotLight::SetStartAttenuation(float InNewStartAttenuation)
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetStartAttenuation(InNewStartAttenuation);
	}
}

void GSpotLight::SetEndAttenuation(float InNewEndAttenuation)
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetEndAttenuation(InNewEndAttenuation);
	}
}

void GSpotLight::SetInnerCorner(float innerCorner)
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetInnerCorner(innerCorner);
	}
}

void GSpotLight::SetOuterCorner(float outerCorner)
{
	if (RSpotLightComponent* pLightComponent = dynamic_cast<RSpotLightComponent*>(const_cast<RLightComponent*>(GetLightComponent())))
	{
		pLightComponent->SetOuterCorner(outerCorner);
	}
}