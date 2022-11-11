#include"Light.hlsl"

SamplerState gsamPointWrap        : register(s0);
SamplerState gsamPointClamp       : register(s1);
SamplerState gsamLinearWrap       : register(s2);
SamplerState gsamLinearClamp      : register(s3);
SamplerState gsamAnisotropicWrap  : register(s4);
SamplerState gsamAnisotropicClamp : register(s5);

Texture2D    SimpleTexture2DMap[TEXTURE2D_MAP_NUM] : register(t3);

cbuffer ObjectConstBuffer :register(b0)
{
	float4x4 WorldMatrix;
	float4x4 ObjectTextureTransform;
	uint MaterialIndex;
	uint RR1;
	uint RR2;
	uint RR3;
}

cbuffer ViewportConstBuffer : register(b1)
{
	float4 ViewportPosition;
	float4x4 ViewProjectionMatrix;
}

cbuffer LightConstBuffer : register(b2)
{
	Light SceneLights[16];
}

struct MaterialConstBuffer
{
	int MaterialType;
	float MaterialRoughness;
	int BaseColorIndex;
	int NormalIndex;

	int SpecularIndex;
	float3 SpecularColor;

	float4 BaseColor;
	float4x4 TransformInformation;
};

StructuredBuffer<MaterialConstBuffer> Materials : register(t4, Space1);
