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

	float4 BaseColor;
	float MaterialRoughness;
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

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	float3 LightDir = normalize(-LightDirection);
	float3 Normal = normalize(MVOut.Normal);

	float4 AmbientLight = { 0.15f, 0.15f, 0.25f,1.0f };
	float4 Specular = { 0.0f, 0.0f, 0.0f,1.0f};
	float3 ViewDir = normalize(ViewportPosition.rgb - MVOut.WorldPosition.rgb);

	RMaterial Material;
	Material.BaseColor = BaseColor;

	//Lambert
	float Diffuse = saturate(dot(Normal, LightDir));
	
	if (MaterialType == 0) 
	{
		//Lambert
	}
	else if (MaterialType == 1) 
	{
		//HalfLambert
		Diffuse = saturate(Diffuse *0.5+0.5);
	}
	else if (MaterialType == 2)
	{
		//Phong
		Diffuse = saturate(Diffuse * 0.5 + 0.5);
		float MaterialShininess = 1.f - saturate(MaterialRoughness);
		float M = MaterialShininess * 100.f;

		float3 ReflectDir = normalize(-reflect(LightDir, Normal));

		Specular.rgb= (M+2.0)*pow(max(dot(ReflectDir, ViewDir), 0.0f), M)/3.1415926;
	}
	else if (MaterialType == 3)
	{
		//BlinnPhong
		Diffuse = saturate(Diffuse * 0.5 + 0.5);
		float MaterialShininess = 1.f - saturate(MaterialRoughness);
		float M = MaterialShininess * 100.f;

		float3 HalfDir = normalize(ViewDir + LightDir);

		Specular.rgb = (M + 2.0) * pow(max(dot(HalfDir, Normal), 0.0f), M) / 3.1415926;
	}
	else if (MaterialType == 4)
	{
		//Wrap Light
		float Wrap = 1.5;
		Diffuse = saturate((Diffuse * Wrap) /(1+ Wrap));
	}
	else if (MaterialType == 5)
	{
		//Minnaert
		float DotView = saturate(dot(Normal, ViewDir));
		float R = 2;
		Diffuse = saturate(Diffuse * pow(Diffuse * DotView, R));
	}
	else if (MaterialType == 6)
	{
		//Banded
		Diffuse = (1.0f + dot(Normal, LightDir)) * 0.5f;
		float Layer = 4;
		Diffuse = floor(Diffuse* Layer)/ Layer;
	}
	else if (MaterialType == 7)
	{
		//GradualBanded
		float4 Color2 = { 0.3f, 0.3f, 0.6f,1.0f };
		float LightDotValue = dot(Normal, LightDir);
		//halflambert
		Diffuse = (1.0f + LightDotValue) * 0.5f;
		float Layer = 4;
		Diffuse = floor(Diffuse * Layer) / Layer;
		lerp(Material.BaseColor, Color2, LightDotValue);
	}
	else if (MaterialType == 8)
	{
		//FinalBanded
		float3 HalfDir = normalize(ViewDir + LightDir);
		float MaterialShininess = 1.f - saturate(MaterialRoughness);
		float M = MaterialShininess * 100.f;

		float3 fresnel0= { 0.05f, 0.05f,0.05f};
		Specular.rgb = SchlickFresnel(fresnel0, Normal, ViewDir, 3) + pow(max(dot(HalfDir, Normal), 0.0f), M)/0.032f ;

		float4 Color2 = { 0.3f, 0.3f, 0.6f,1.0f };
		float LightDotValue = dot(Normal, LightDir);
		//halflambert
		Diffuse = (1.0f + LightDotValue) * 0.5f;
		float Layer = 4;
		Diffuse = floor(Diffuse * Layer) / Layer;
		lerp(Material.BaseColor, Color2, LightDotValue);
	}


	MVOut.Color = Material.BaseColor * Diffuse 
		+ AmbientLight * Material.BaseColor 
		+ Specular* Material.BaseColor;
	return MVOut.Color;
}