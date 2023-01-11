#include "Material.hlsl"

struct MeshVertexIn
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 PositionH : SV_POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord  : TEXCOORD;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	MeshVertexOut Out = (MeshVertexOut)0;
	float3 ViewDirection = normalize(ViewportPosition.xyz - MV.Position);
	float dis = length(ViewDirection);
	Out.WorldPosition = mul(float4(MV.Position, 1.0f), WorldMatrix);
	Out.WorldPosition += float4(normalize(MV.Normal),0)*dis*0.1;


	Out.PositionH = mul(Out.WorldPosition, ViewProjectionMatrix);

	//ui×ø±ê
	float4 MyTexCoord = mul(float4(MV.TexCoord, 0.0f, 1.f), ObjectTextureTransform);
	Out.TexCoord = mul(MyTexCoord, MatConstBuffer.TransformInformation).xy;

	//·¨Ïß
	Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	return float4(0.f, 0.f, 1.f, 0.15f) ;
}