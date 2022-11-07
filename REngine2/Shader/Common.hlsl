#include "Material.hlsl"
#include "Light.hlsl"
#include"PBR.hlsl"

SamplerState TextureSampler: register(s0);
SamplerState AnisotropicSampler : register(s1);

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

StructuredBuffer<MaterialConstBuffer> Materials : register(t4, Space1);

struct MeshVertexIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
	float2 TexCoord: TEXCOORD;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
	float2 TexCoord: TEXCOORD;
};