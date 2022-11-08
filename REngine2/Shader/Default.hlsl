#include"Common.hlsl"

struct MeshVertexIn
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
	float2 TexCoord: TEXCOORD;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float3 Normal : NORMAL;
	float3 UTangent : TANGENT;
	float2 TexCoord: TEXCOORD;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	MeshVertexOut Out;

	//世界坐标
	Out.WorldPosition = mul(float4(MV.Position, 1.f), WorldMatrix);

	//变换到齐次剪辑空间
	Out.Position = mul(Out.WorldPosition, ViewProjectionMatrix);

	Out.Normal = mul(MV.Normal, (float3x3)WorldMatrix);

	Out.Color = MV.Color;

	//切线
	Out.UTangent = mul(MV.UTangent, (float3x3)WorldMatrix);

	//ui坐标
	float4 MyTexCoord = mul(float4(MV.TexCoord, 0.0f, 1.f), ObjectTextureTransform);
	Out.TexCoord = mul(MyTexCoord, MatConstBuffer.TransformInformation).xy;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{	
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	RMaterial Material;
	if (MatConstBuffer.BaseColorIndex != -1)
	{
		Material.DiffuseAlbedo =SimpleTexture2DMap[MatConstBuffer.BaseColorIndex].Sample(gsamLinearWrap, MVOut.TexCoord);
	}
	else 
	{
		Material.DiffuseAlbedo = MatConstBuffer.BaseColor;
	}
	Material.Shininess = 1.0f - MatConstBuffer.MaterialRoughness;
	Material.FresnelR0 = 0.3f;

	float3 AmbientLight = { 0.15f, 0.15f, 0.25f };

	MVOut.Normal = normalize(MVOut.Normal);

	float3 View2Eye = ViewportPosition.rgb - MVOut.WorldPosition.rgb;
	float Dist2Eye = length(View2Eye);
	View2Eye /= Dist2Eye;


	float3 directLight = ComputeDirectionalLight(SceneLights[0], Material, MVOut.Normal, View2Eye);

	float3 r = reflect(-View2Eye, MVOut.Normal);
	//float4 reflectionColor = gCubeMap.Sample(gsamLinearWrap, r);
	float3 fresnelFactor = SchlickFresnel(Material.FresnelR0, MVOut.Normal, r,5);

	MVOut.Color.xyz = AmbientLight + directLight+ Material.Shininess * fresnelFactor;
	MVOut.Color.w = 1;
	return MVOut.Color;
}