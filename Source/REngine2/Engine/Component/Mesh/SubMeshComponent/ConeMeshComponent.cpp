#include"ConeMeshComponent.h"
#include"../../../Mesh/MeshType.h"
ConeMeshComponent::ConeMeshComponent()
{

}

void ConeMeshComponent::CreateMesh(MeshRenderData& MeshData, float InRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
	//�뾶���
	float RadiusInterval = -InRadius / (float)InHeightSubdivision;
	//�߶ȼ��
	float HeightInterval = InHeight / (float)InHeightSubdivision;

	float BetaValue = XM_2PI / (float)InAxialSubdivision;

	//��������
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 0.5f * InHeight, 0.f), XMFLOAT4(Colors::White)));

	uint32_t Index = MeshData.VertexData.size();

	for (uint32_t i = 0; i < InHeightSubdivision; ++i)
	{
		float Y = 0.5f * InHeight - HeightInterval * i;
		float Radius = i * RadiusInterval;
		for (uint32_t j = 0; j <= InAxialSubdivision; ++j)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					Radius * cosf(j * BetaValue),//x
					Y,//y
					Radius * sinf(j * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}
	}

	//����е�
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, -0.5f * InHeight, 0.f), XMFLOAT4(Colors::White)));

	//����indexģ��
	for (uint32_t i = 0; i < InAxialSubdivision; ++i)
	{
		MeshData.IndexData.push_back(0);
		MeshData.IndexData.push_back(i + 1);
		MeshData.IndexData.push_back(i);
	}

	float BaseIndex = 1;
	float VertexCircleNum = InAxialSubdivision + 1;
	//������Χ
	for (uint32_t i = 0; i < InHeightSubdivision - 2; ++i)
	{
		for (uint32_t j = 0; j < InAxialSubdivision; ++j)
		{
			//���ǻ��Ƶ����ı���
			//������1
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j);
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j);
			//������2
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j);
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j + 1);
		}
	}

	//�����ϼ�
	uint32_t SouthBaseIndex = MeshData.VertexData.size() - 1;
	BaseIndex = SouthBaseIndex - VertexCircleNum;
	for (uint32_t Index = 0; Index < InAxialSubdivision; ++Index)
	{
		MeshData.IndexData.push_back(SouthBaseIndex);
		MeshData.IndexData.push_back(BaseIndex + Index);
		MeshData.IndexData.push_back(BaseIndex + Index + 1);
	}
}

void ConeMeshComponent::BuildKey(size_t& outKey, float radius, float height, uint32_t axialSub, uint32_t heightSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 2;
	outKey += floatHash(radius);
	outKey += floatHash(height);

	outKey += intHash(axialSub);
	outKey += intHash(heightSub);
}

