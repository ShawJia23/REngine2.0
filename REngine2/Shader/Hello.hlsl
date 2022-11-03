#include "Material.hlsl"
#include "Light.hlsl"

cbuffer ObjectConstBuffer :register(b0)//b0->b14
{
	float4x4 WorldMatrix;
}

cbuffer ViewportConstBuffer : register(b1)//b0->b14
{
	float4 ViewportPosition;
	float4x4 ViewProjectionMatrix;
}

cbuffer MaterialConstBuffer : register(b2)//b0->b14
{	
	int MaterialType;

	float4 BaseColor; 
	float MaterialRoughness;
	float4x4 TransformInformation;
}

cbuffer LightConstBuffer : register(b3)//b0->b14
{
	Light SceneLights[16];
}

struct MeshVertexIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent: TANGENT;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out;

	//世界坐标
	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);

	//变换到齐次剪辑空间
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);
	Out.Color.rgb = MV.Normal.rgb;

	if (MaterialType == 13)
	{
		Out.Normal = MV.Normal;
	}
	else
	{
		//转法线
		Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);
	}
	
	//切线
	Out.UTangent = MV.UTangent;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{	
	RMaterial Material;
	Material.BaseColor = BaseColor;

	//BaseColor
	if (MaterialType == 12)
	{
		return Material.BaseColor;
	}
	else if (MaterialType == 13)
	{
		return float4(MVOut.Normal, 1.f);
	}
	else if (MaterialType == 14)
	{
		return float4(MVOut.Normal,1.f);
	}

	float4 AmbientLight = { 0.15f, 0.15f, 0.25f, 1.0f };
	float3 ModelNormal = normalize(MVOut.Normal);

	float DotValue = 0;

	float4 LightStrengths = { 0.f,0.f,0.f,1.f };
	float4 Specular = { 0.f,0.f,0.f,1.f };

	for (int i = 0; i < 16; i++)
	{
		if (length(SceneLights[i].LightIntensity.xyz) > 0.f)
		{
			float3 NormalizeLightDirection = normalize(GetLightDirection(SceneLights[i],MVOut.WorldPosition.xyz));

			float4 LightStrength = ComputeLightStrength(SceneLights[i], ModelNormal, MVOut.WorldPosition.xyz, NormalizeLightDirection);

			DotValue = pow(max(dot(ModelNormal, NormalizeLightDirection), 0.0),2.f);

			LightStrengths += LightStrength * DotValue * float4(SceneLights[i].LightIntensity,1.f);
			LightStrengths.w = 1.f;
		}
	}

	//最终颜色贡献
	MVOut.Color = LightStrengths*Material.BaseColor //漫反射

		+AmbientLight * Material.BaseColor; //间接光
	
	return MVOut.Color;
}