
#include"Material.hlsl"

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
	Material.DiffuseAlbedo = GetMaterialDiffuse(MatConstBuffer, MVOut.TexCoord);
	Material.SpecularAlbedo = GetMaterialSpecular(MatConstBuffer, MVOut.TexCoord);
	Material.Shininess = 1.0f - MatConstBuffer.MaterialRoughness;
	Material.FresnelR0 = 0.03f;

	MVOut.Normal = normalize(MVOut.Normal);

	//模型法线
	float3 ModelNormal = GetMaterialNormal(MatConstBuffer, MVOut.TexCoord, MVOut.Normal, MVOut.UTangent);

	//归一化的摄像机到物体的向量
	float3 View2Eye = ViewportPosition.rgb - MVOut.WorldPosition.rgb;
	float Dist2Eye = length(View2Eye);
	View2Eye /= Dist2Eye;

	//float3 AmbientLight = { 0.f, 0.f, 0.f };
	float3 AmbientLight = { 0.2f, 0.2f, 0.2f };

	float3 directLight = ComputeDirectionalLight(SceneLights[0], Material, ModelNormal, View2Eye);

	float3 r = reflect(-View2Eye, ModelNormal);
	float3 fresnelFactor = SchlickFresnel(Material.FresnelR0, ModelNormal, r,5);

	MVOut.Color.xyz = AmbientLight + directLight+ Material.Shininess * fresnelFactor;
	MVOut.Color.w = 1;
	return MVOut.Color;
}