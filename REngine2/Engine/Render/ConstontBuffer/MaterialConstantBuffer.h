#pragma once
#include"../../EngineMinimal.h"
struct RMaterialConstantBuffer
{
	RMaterialConstantBuffer();

	int MaterialType;
	float	 Roughness;
	int BaseColorIndex;
	int NormalIndex;

	int SpecularIndex;
	XMFLOAT3 SpecularColor;

	DirectX::XMFLOAT4 BaseColor;
	DirectX::XMFLOAT4X4 TransformInformation;
};
