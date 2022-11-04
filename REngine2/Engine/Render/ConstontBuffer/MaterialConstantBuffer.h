#pragma once
#include"../../EngineMinimal.h"
struct RMaterialConstantBuffer
{
	RMaterialConstantBuffer();

	int MaterialType;
	int Reserved1;
	int Reserved2;
	int Reserved3;

	DirectX::XMFLOAT4 BaseColor;
	float	 Roughness;
	DirectX::XMFLOAT4X4 TransformInformation;
};
