#include"ParallelLight.h"
#include"../../Component/Light/ParallelLightComponent.h"
GParallelLight::GParallelLight()
{
	SetLightComponent(CreateObject<RParallelLightComponent>(new RParallelLightComponent()));
}

void GParallelLight::Tick(float DeltaTime)
{
	fvector_3d v3 = GetRotation();

	v3.x += DeltaTime * 10.f;
	v3.y += DeltaTime * 10.f;
	//v3.z += DeltaTime * 100.f;

	SetRotation(v3);
}