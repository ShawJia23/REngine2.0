#include"ParallelLight.h"
#include"../Component/Light/ParallelLightComponent.h"

GParallelLight::GParallelLight()
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "ParallelLightComponent";
	SetLightComponent(CreateObject<RParallelLightComponent>(param, new RParallelLightComponent()));
}

void GParallelLight::Tick(GameTimer& gt)
{
	fvector_3d v3 = GetRotation();

	float time = gt.DeltaTime();

	v3.x += gt.DeltaTime() * 5.f;
	v3.y += gt.DeltaTime() * 5.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}