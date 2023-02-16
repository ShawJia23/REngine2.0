#include"ParallelLight.h"
#include"../Component/Light/ParallelLightComponent.h"

GParallelLight::GParallelLight()
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "ParallelLightComponent";
	SetLightComponent(CreateObject<RParallelLightComponent>(param, new RParallelLightComponent()));
}

void GParallelLight::Tick(float DeltaTime)
{
	fvector_3d v3 = GetRotation();

	v3.x += DeltaTime * 2.f;
	v3.y += DeltaTime * 2.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}