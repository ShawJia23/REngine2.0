#include "Material.hlsl"

struct MeshVertexIn
{
	float3 Position : POSITION;
	float2 TexCoord: TEXCOORD;
};

struct MeshVertexOut
{
	float4 WorldPosition : POSITION;
	float4 PositionH : SV_POSITION;
	float2 TexCoord: TEXCOORD;
};

MeshVertexOut VertexShaderMain(MeshVertexIn MV)
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	MeshVertexOut Out = (MeshVertexOut)0;

	Out.WorldPosition = mul(float4(MV.Position, 1.0f), WorldMatrix);

	Out.PositionH = mul(Out.WorldPosition, ViewProjectionMatrix);

	//ui����
	float4 MyTexCoord = mul(float4(MV.TexCoord, 0.0f, 1.f), ObjectTextureTransform);
	Out.TexCoord = mul(MyTexCoord, MatConstBuffer.TransformInformation).xy;

	return Out;
}

float4 PixelShaderMain(MeshVertexOut MVOut) :SV_TARGET
{
	MaterialConstBuffer MatConstBuffer = Materials[MaterialIndex];

	return MatConstBuffer.BaseColor;
	//float R = SampleBuildCDTexture(MVOut.TexCoord);

	//R += MatConstBuffer.Param0;//CD������
	//R = floor(R);

	//R *= 0.5f;//����͸��
	//R *= 1.f;//CD����

	//float4 BaseColor = GetMaterialBaseColor(MatConstBuffer, MVOut.TexCoord);

	//float Alpha = abs(BaseColor.a * R + BaseColor.r);

	////��Ҫ���ڲý�
	//if (Alpha <= 0.1f)
	//{
	//	Alpha = 0.f;
	//}

	//return float4(1.f, 1.f, 0.f, Alpha);
}