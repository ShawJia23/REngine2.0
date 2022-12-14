#pragma once
#include"../../EngineMinimal.h"

struct RLight
{
	RLight();

	XMFLOAT3 LightIntensity;
	float StartAttenuation;
	XMFLOAT3 LightDirection;
	float EndAttenuation;
	XMFLOAT3 Position;
	int LightType;

	float InnerCorner;
	float OuterCorner;
	float x1;
	float x2;
};

struct RLightConstantBuffer
{
	RLightConstantBuffer();

	RLight SceneLights[16];
};
