
struct RMaterial
{
	float4 BaseColor;
};

// 石里克近似来逼近菲涅尔的效果 (see pg. 233 "Real-Time Rendering 3rd Ed.").
// R0 = ( (n-1)/(n+1) )^2, where n is the index of refraction.
float3 SchlickFresnel(float3 FresnelR0, float3 Normal, float3 ViewVec,int PowM)
{
    float f0 = pow(1.0f - saturate(dot(Normal, ViewVec)), PowM);
    return FresnelR0 + (1.0f - FresnelR0) * f0;
}