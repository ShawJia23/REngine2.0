#pragma once
#include"../../EngineMinimal.h"
struct RLightConstantBuffer
{
	RLightConstantBuffer();

	XMFLOAT3 LightIntensity;
	XMFLOAT3 LightDirection;
};
