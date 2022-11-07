
struct MaterialConstBuffer
{
	int MaterialType;
	float MaterialRoughness;
	int BaseColorIndex;
	int NormalIndex;

	float4 BaseColor;
	float4x4 TransformInformation;
};

struct RMaterial
{
	float4 BaseColor;
};

float4 GetMaterialBaseColor(MaterialConstBuffer MatConstBuffer, float2 InTexCoord)
{
	if (MatConstBuffer.BaseColorIndex != -1)
	{
		return SimpleTexture2DMap[MatConstBuffer.BaseColorIndex].Sample(TextureSampler, InTexCoord);
	}

	return MatConstBuffer.BaseColor;
}