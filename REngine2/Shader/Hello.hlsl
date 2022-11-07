#include "Material.hlsl"
#include "Light.hlsl"

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	MeshVertexOut Out;

	//��������
	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);

	//�任����μ����ռ�
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);

	if (MatConstBuffer.MaterialType == 13)
	{
		Out.Normal = MV.Normal;
	}
	else
	{
		//ת����
		Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);
	}

	//����
	Out.UTangent = mul(MV.UTangent, (float3x3)WorldMatrix);

	//ui����
	float4 MyTexCoord = mul(float4(MV.TexCoord, 0.0f, 1.f), ObjectTextureTransform);
	Out.TexCoord = mul(MyTexCoord, MatConstBuffer.TransformInformation).xy;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{	
	RMaterial Material;
	//��ȡBaseColor
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

	//������ɫ����
	MVOut.Color = LightStrengths*Material.BaseColor //������

		+AmbientLight * Material.BaseColor; //��ӹ�
	
	return MVOut.Color;
}