
float4 GetDistributionGGX(float3 Normal, float3 Half, float Roughness) 
{
	float Pi = 3.1415926;

	float a2 = pow(Roughness, 4);
	float NoH = saturate(dot(Normal, Half));
	float d = (NoH * NoH * (a2 - 1) + 1);

	return a2 / max(d * d * Pi, 0.001);
}

// 石里克近似来逼近菲涅尔的效果 (see pg. 233 "Real-Time Rendering 3rd Ed.").
// R0 = ( (n-1)/(n+1) )^2, where n is the index of refraction.
float3 SchlickFresnel(float3 FresnelR0, float3 Normal, float3 ViewVec, int PowM)
{
	float f0 = pow(1.0f - saturate(dot(Normal, ViewVec)), PowM);
	return FresnelR0 + (1.0f - FresnelR0) * f0;
}

float3 SchlickGGX(float3 NoV, float Roughness)
{
	float K_Dir = pow(Roughness, 2) / 8.0f;
	
	return NoV / max(K_Dir + (1 - K_Dir) * NoV, 0.001);
}

float GSmith(float3 Normal, float3 ViewDir, float3 LightDir, float Roughness) 
{
	float NoV = saturate(dot(Normal, ViewDir));
	float NoL = saturate(dot(Normal, LightDir));

	return SchlickGGX(NoV, Roughness) * SchlickGGX(NoL, Roughness);
}
