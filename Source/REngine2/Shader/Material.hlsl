#include"Common.hlsl"

float4 GetMaterialDiffuse(MaterialConstBuffer mat, float2 texCoord)
{
	if (mat.BaseColorIndex != -1)
	{
		return SimpleTexture2DMap[mat.BaseColorIndex].Sample(gsamLinearWrap, texCoord);
	}
	else
		return  mat.BaseColor;
}

float3x3 GetBuildTBNMatrix(float3 unitWorldNormal, float3 worldTangent)
{
	float3 N = unitWorldNormal;

	//矫正 万一原来的切线和法线不是垂直
	float3 T = normalize(worldTangent - dot(worldTangent, N) * N);

	float3 B = cross(N, T);

	return float3x3(T, B, N);
}

float3 GetMaterialNormal(MaterialConstBuffer mat, float2 texCoord, float3 unitWorldNormal, float3 worldTangent)
{
	if (mat.NormalIndex != -1)
	{
		float4 SampleNormal = SimpleTexture2DMap[mat.NormalIndex].Sample(gsamLinearWrap, texCoord);

		//[0,1]->[-1,1] => [0,1] * 2.f = [0,2] => [0-2]-1.f = [-1,1];
		float3 NormalsInTangentSpace = 2.0f * SampleNormal.rgb - 1.f;

		//拿到世界TBN
		float3x3 TBN = GetBuildTBNMatrix(unitWorldNormal, worldTangent);

		//把切线空间下的采样法线转为世界的法线
		return mul(NormalsInTangentSpace, TBN);
	}
	else
		return unitWorldNormal;
}

float4 GetMaterialSpecular(MaterialConstBuffer mat, float2 texCoord)
{
	if (mat.SpecularIndex != -1)
	{
		return SimpleTexture2DMap[mat.SpecularIndex].Sample(gsamLinearWrap, texCoord);
	}
	else 
		return float4(mat.SpecularColor, 1.f);
}