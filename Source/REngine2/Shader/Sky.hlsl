#include "Common.hlsl"

struct MeshVertexIn
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct MeshVertexOut
{
	float4 PositionH : SV_POSITION;
	float3 PositionL : POSITION;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out = (MeshVertexOut)0;

	Out.PositionL = MV.Position;

	//世界坐标
	float4 WorldPosition = mul(float4(Out.PositionL,1.0f), WorldMatrix);

	//变换到齐次剪辑空间
	Out.PositionH = mul(WorldPosition, ViewProjectionMatrix);

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	return SimpleCubeMap.Sample(gsamLinearWrap, MVOut.PositionL);
//return float4(0.f,0.f,0.f,1.f);
}