#include"PlaneMeshComponent.h"
#include"../../../Mesh/MeshType.h"
PlaneMeshComponent::PlaneMeshComponent()
{

}

void PlaneMeshComponent::CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, uint32_t InHeightSubdivide, uint32_t InWidthSubdivide)
{
	auto SubdivideValue = [&](float InValue, uint32_t InSubdivideValue)->float
	{
		if (InSubdivideValue <= 1)
		{
			return InValue;
		}

		return InValue / ((float)InSubdivideValue - 1);
	};

	float CHeight = 0.5f * InHeight;
	float CWidth = 0.5f * InWidth;

	float HeightSubdivideValue = SubdivideValue(InHeight, InHeightSubdivide);
	float WidthSubdivideValue = SubdivideValue(InWidth, InWidthSubdivide);

	//���Ƶ��λ��
	for (uint32_t i = 0; i < InHeightSubdivide; ++i)
	{
		float Z = CHeight - i * HeightSubdivideValue;
		for (uint32_t j = 0; j < InWidthSubdivide; ++j)
		{
			float X = CWidth - j * WidthSubdivideValue;
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					X,//x
					0.f,//y
					Z), //z
				XMFLOAT4(Colors::Gray), XMFLOAT3(0.f, 1.f, 0.f)));
		}
	}

	//����index
	for (uint32_t i = 0; i < InHeightSubdivide - 1; ++i)
	{
		for (uint32_t j = 0; j < InWidthSubdivide - 1; ++j)
		{
			////���ǻ��Ƶ����ı���
			////������1
			//MeshData.IndexData.push_back( i * InWidthSubdivide + j);
			//MeshData.IndexData.push_back( i * InWidthSubdivide + j + 1);
			//MeshData.IndexData.push_back( (i + 1) * InWidthSubdivide + j);

			////������2
			//MeshData.IndexData.push_back( (i + 1) * InWidthSubdivide + j);
			//MeshData.IndexData.push_back( i * InWidthSubdivide + j + 1);
			//MeshData.IndexData.push_back( (i + 1) * InWidthSubdivide + j + 1);

			//���ǻ��Ƶ����ı���
			//������1
			MeshData.IndexData.push_back((i + 1) * InWidthSubdivide + j);
			MeshData.IndexData.push_back(i * InWidthSubdivide + j + 1);
			MeshData.IndexData.push_back(i * InWidthSubdivide + j);

			//������2
			MeshData.IndexData.push_back((i + 1) * InWidthSubdivide + j + 1);
			MeshData.IndexData.push_back(i * InWidthSubdivide + j + 1);
			MeshData.IndexData.push_back((i + 1) * InWidthSubdivide + j);
		}
	}
}

void PlaneMeshComponent::BuildKey(size_t& outKey, float height, float width, uint32_t heightSub, uint32_t widthSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 4;
	outKey += floatHash(height);
	outKey += floatHash(width);
	outKey += intHash(heightSub);
	outKey += intHash(widthSub);
}

