#include "Light.h"
#include"../Component/Light/LightComponent.h"
#include"../Core/Construction/ObjectConstruction.h"

#pragma region GLight

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

#pragma endregion

#pragma region GParallelLight

GParallelLight::GParallelLight()
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightComponent(CreateObject<RParallelLightComponent>(param,new RParallelLightComponent()));
}

void GParallelLight::Tick(float DeltaTime)
{
	fvector_3d v3 = GetRotation();

	v3.x += DeltaTime * 2.f;
	v3.y += DeltaTime * 2.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}

#pragma endregion

#pragma region GPointLight


GPointLight::GPointLight()
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightComponent(CreateObject<RPointLightComponent>(param,new RPointLightComponent()));
}

void GPointLight::Tick(float DeltaTime)
{
	fvector_3d v3 = GetRotation();

	//v3.x += DeltaTime * 10.f;
	//v3.y += DeltaTime * 10.f;
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

#pragma endregion

#pragma region GSpotLight

float index_test;
GSpotLight::GSpotLight()
{
	CreateObjectParam param;
	param.Outer = this;
	SetLightComponent(CreateObject<RSpotLightComponent>(param,new RSpotLightComponent()));
	index_test = 0;
}

void GSpotLight::Tick(float DeltaTime)
{
	index_test += DeltaTime;

	float O = 50.f;
	float I = 30.f;

	SetInnerCorner(I * fabsf(cos(index_test)) + 10.f);
	SetOuterCorner(O * fabsf(cos(index_test)) + 20.f);

	fvector_3d v3 = GetRotation();

	v3.x += DeltaTime * 10.f;
	v3.y += DeltaTime * 10.f;
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

#pragma endregion