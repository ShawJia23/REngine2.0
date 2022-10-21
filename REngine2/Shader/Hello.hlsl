
cbuffer ObjectConstBuffer :register(b0)
{
	float4x4 WorldMatrix;
}

cbuffer ViewportConstBuffer : register(b1)
{
	float4x4 ViewProjectionMatrix;
}

cbuffer MaterialConstBuffer : register(b2)
{
	float4x4 TransformInformation;
}

cbuffer LightConstBuffer : register(b3)
{
	float3 LightIntensity;
	float3 LightDirection;
}


struct MeshVertexIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
};

struct MeshVertexOut
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out;

	float4 Position = mul(float4(MV.Position, 1.f), WorldMatrix);
	Out.Position = mul(Position, ViewProjectionMatrix);

	Out.Normal= mul(MV.Normal, (float3x3)WorldMatrix);

	float3  Normal = normalize(Out.Normal);

	float3  LightDir = normalize(-LightDirection);
	float DotValue=max(dot(Normal, LightDir),0.f);

	Out.Color = MV.Color * DotValue;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	return MVOut.Color;
}