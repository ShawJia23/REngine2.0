#include "Material.hlsl"
#include "Light.hlsl"

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	MeshVertexOut Out;

	//世界坐标
	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);

	//变换到齐次剪辑空间
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);

	if (MatConstBuffer.MaterialType == 13)
	{
		Out.Normal = MV.Normal;
	}
	else
	{
		//转法线
		Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);
	}

	//切线
	Out.UTangent = mul(MV.UTangent, (float3x3)WorldMatrix);

	//ui坐标
	float4 MyTexCoord = mul(float4(MV.TexCoord, 0.0f, 1.f), ObjectTextureTransform);
	Out.TexCoord = mul(MyTexCoord, MatConstBuffer.TransformInformation).xy;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{	
	RMaterial Material;
	//获取BaseColor
	Material.BaseColor = GetMaterialBaseColor(MatConstBuffer, MVOut.TexCoord);

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