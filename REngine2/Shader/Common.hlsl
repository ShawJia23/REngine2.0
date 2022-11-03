#include "Material.hlsl"
#include "Light.hlsl"
#include"PBR.hlsl"
cbuffer ObjectConstBuffer :register(b0)
{
	float4x4 WorldMatrix;
}

cbuffer ViewportConstBuffer : register(b1)
{
	float4 ViewportPosition;
	float4x4 ViewProjectionMatrix;
}

cbuffer MaterialConstBuffer : register(b2)
{
	int MaterialType;

	float4 BaseColor;
	float MaterialRoughness;
	float4x4 TransformInformation;
}

cbuffer LightConstBuffer : register(b3)
{
	Light SceneLights[16];
}
struct MeshVertexIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
};