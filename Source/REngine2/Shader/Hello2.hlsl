#include "Common.hlsl"
MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out;

	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);

	Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);
	Out.UTangent = MV.UTangent;
	Out.Color = MV.Color;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	RMaterial Material;
	Material.BaseColor = BaseColor;


	float3 Normal = normalize(MVOut.Normal);

	float3 AmbientLight = { 0.15f, 0.15f, 0.25f};
	float3 Specular = { 0.0f, 0.0f, 0.0f};
	float3 ViewDir = normalize(ViewportPosition.rgb - MVOut.WorldPosition.rgb);

	float3 LightStrength = { 0.f,0.f,0.f};

	float3 LightDir = normalize(GetLightDirection(SceneLights[0], MVOut.WorldPosition));

	LightStrength = ComputeLightStrength(SceneLights[0], LightDir);

	float Diffuse = pow(max(dot(Normal, LightDir), 0.0), 2.f);

	LightStrength = LightStrength*Diffuse;


	MVOut.Color.xyz = LightStrength * (Material.BaseColor + Specular * Material.BaseColor)
		+ AmbientLight * Material.BaseColor;
		return MVOut.Color;
}