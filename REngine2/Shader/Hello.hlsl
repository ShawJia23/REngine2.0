#include "Material.hlsl"

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

	float MaterialRoughness;
	float4 BaseColor;
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
	float4 WorldPosition : POSITION;
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MeshVertexOut Out;

	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);

	Out.Normal= mul(MV.Normal, (float3x3)WorldMatrix);

	Out.Color = MV.Color ;

	return Out;
}

// 石里克近似来逼近菲涅尔的效果 (see pg. 233 "Real-Time Rendering 3rd Ed.").
// R0 = ( (n-1)/(n+1) )^2, where n is the index of refraction.
float3 SchlickFresnel(float3 R0, float3 normal, float3 lightVec)
{
	float cosIncidentAngle = saturate(dot(normal, lightVec));

	float f0 = 1.0f - cosIncidentAngle;
	float3 reflectPercent = R0 + (1.0f - R0) * (f0 * f0 * f0 * f0 * f0);

	return reflectPercent;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	float3  LightDir = normalize(-LightDirection);
	float3 Normal = normalize(MVOut.Normal);

	float4 AmbientLight = { 0.15f, 0.15f, 0.25f,1.0f };
	float4 Specular = { 0.0f, 0.0f, 0.0f,1.0f};

	RMaterial Material;
	Material.BaseColor = BaseColor;

	float Diffuse = dot(Normal, LightDir);
	
	if (MaterialType == 0) 
	{
		//Lambert
		Diffuse = max(Diffuse, 0.f);
	}
	else if (MaterialType == 1) 
	{
		//HalfLambert
		Diffuse = max(Diffuse *0.5+0.5, 0.f);
	}
	else if (MaterialType == 2)
	{
		//Phong
		Diffuse = max(Diffuse * 0.5 + 0.5, 0.f);

		float3 ViewDirection = normalize(ViewportPosition.rgb-MVOut.WorldPosition.rgb);
		float3 halfVec = normalize(ViewDirection + LightDir);

		float MaterialShininess = 1.f - saturate(MaterialRoughness);
		float M = MaterialShininess * 256.f;

		Specular.rgb = pow(max(dot(halfVec, Normal), 0.0f), M);

		Specular = Specular / (Specular + 1.0f);
	}


	MVOut.Color = Material.BaseColor * Diffuse 
		+ AmbientLight * Material.BaseColor 
		+ Specular* Material.BaseColor;
	return MVOut.Color;
}