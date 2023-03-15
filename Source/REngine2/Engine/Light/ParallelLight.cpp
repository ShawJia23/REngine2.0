#include"ParallelLight.h"
#include"../Component/Light/ParallelLightComponent.h"
#include"../Construction/MacroConstruction.h"
GParallelLight::GParallelLight()
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT(this->GetTransformationComponent(), this);
	SetLightComponent(CreateObject<RParallelLightComponent>(inObjectParam, new RParallelLightComponent()));
}

void GParallelLight::Tick(GameTimer& gt)
{
	fvector_3d v3 = GetRotation();

	float time = gt.DeltaTime();

	v3.x += gt.DeltaTime() * RotateSpeed.x;
	v3.y += gt.DeltaTime() * RotateSpeed.y;
	v3.z += gt.DeltaTime() * RotateSpeed.z;

	SetRotation(v3);
}