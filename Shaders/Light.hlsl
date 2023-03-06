
struct Light
{
	float3 LightIntensity;
	float  StartAttenuation;
	float3 LightDirection;
	float  EndAttenuation;
	float3 Position;
	int LightType;

	float InnerCorner;
	float OuterCorner;
	float x1;
	float x2;
};

struct RMaterial
{
	float4 DiffuseAlbedo;
	float4 SpecularAlbedo;
	float3 FresnelR0;
	float Shininess;
};

// 石里克近似来逼近菲涅尔的效果 (see pg. 233 "Real-Time Rendering 3rd Ed.").
// R0 = ( (n-1)/(n+1) )^2, where n is the index of refraction.
float3 SchlickFresnel(float3 FresnelR0, float3 Normal, float3 ViewVec, int PowM)
{
	float f0 = pow(1.0f - saturate(dot(Normal, ViewVec)), PowM);
	return FresnelR0 + (1.0f - FresnelR0) * f0;
}

float3 BlinnPhong(float3 lightStrength, float3 lightVec, float3 normal, float3 toEye, RMaterial mat)
{
	const float m = mat.Shininess * 256.0f;
	float3 halfVec = normalize(toEye + lightVec);

	float roughnessFactor = (m + 8.0f) * pow(max(dot(halfVec, normal), 0.0f), m) / 8.0f;
	float3 fresnelFactor = SchlickFresnel(mat.FresnelR0, halfVec, lightVec,5);

	float3 specAlbedo = mat.SpecularAlbedo.rgb;
	specAlbedo *= fresnelFactor * roughnessFactor;

	// Our spec formula goes outside [0,1] range, but we are 
	// doing LDR rendering.  So scale it down a bit.
	specAlbedo = specAlbedo / (specAlbedo + 1.0f);

	return (mat.DiffuseAlbedo.rgb + specAlbedo) * lightStrength;
}

float3 ComputeDirectionalLight(Light L, RMaterial mat, float3 normal, float3 toEye)
{
	// The light vector aims opposite the direction the light rays travel.
	float3 lightVec = -L.LightDirection;

	// Scale light down by Lambert's cosine law.
	float ndotl = max(dot(lightVec, normal), 0.0f);

	float3 lightStrength = L.LightIntensity * ndotl;

	//return CartoonLight(lightStrength, lightVec, normal, toEye, mat);
	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

////计算光纤
//float4 ComputeLighting(Light gLights, RMaterial mat,
//	float3 pos, float3 normal, float3 View2Eye,
//	float3 shadowFactor)
//{
//	float3 result = 0.0f;
//
//	int i = 0;
////
////#if (NUM_DIR_LIGHTS > 0)
////	for (i = 0; i < NUM_DIR_LIGHTS; ++i)
////	{
////		result += shadowFactor[i] * ComputeDirectionalLight(gLights[i], mat, normal, toEye);
////	}
////#endif
////
////#if (NUM_POINT_LIGHTS > 0)
////	for (i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; ++i)
////	{
////		result += ComputePointLight(gLights[i], mat, pos, normal, toEye);
////	}
////#endif
////
////#if (NUM_SPOT_LIGHTS > 0)
//	//for (i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS; ++i)
//	//{
//	//	result += ComputeSpotLight(gLights[i], mat, pos, normal, toEye);
//	//}
////#endif 
//	//return float4(result, 0.0f);
//	return ComputeDirectionalLight(gLights, mat, normal, View2Eye);
//}