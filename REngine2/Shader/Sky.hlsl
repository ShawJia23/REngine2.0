#include "Common.hlsl"

struct MeshVertexIn
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct MeshVertexOut
{
	float4 PositionH : POSITION;
	float4 PositionL : SV_POSITION;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out = (MeshVertexOut)0;

	Out.PositionH = float4(MV.Position, 1.f);

	//世界坐标
	float4 WorldPosition = mul(Out.PositionH, WorldMatrix);

	//变换到齐次剪辑空间
	Out.PositionL = mul(WorldPosition, ViewProjectionMatrix);

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	//return SimpleCubeMap.Sample(TextureSampler, MVOut.PositionH);
	return float4(0.5f,0.f,0.f,1.f);
}