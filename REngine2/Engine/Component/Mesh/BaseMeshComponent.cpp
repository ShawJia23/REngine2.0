#include"BaseMeshComponent.h"
#include"../../Mesh/Core/MeshType.h"
#include"../../LoadAsset/ObjectAnalysis.h"
BoxMeshComponent::BoxMeshComponent()
{

}

void BoxMeshComponent::CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, float InDepth)
{
	float CHeight = 0.5f * InHeight;
	float CWidth = 0.5f * InWidth;
	float CDepth = 0.5f * InDepth;

	//��������
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, -CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, -CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, -CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, -CHeight, CDepth), XMFLOAT4(Colors::White)));

	//��������
	//ǰ
	MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(2);
	MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(2); MeshData.IndexData.push_back(3);

	//��
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(5);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(7); MeshData.IndexData.push_back(6);

	//��
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(5); MeshData.IndexData.push_back(1);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(0);

	//��
	MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(2); MeshData.IndexData.push_back(6);
	MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(7);

	//��
	MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(5); MeshData.IndexData.push_back(6);
	MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(2);

	//��
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(3);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(7);
}

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

CustomMeshComponent::CustomMeshComponent()
{

}

void CustomMeshComponent::CreateMesh(MeshRenderData& MeshData, string path)
{
	ObjectAnalysisByAssimp lod;
	lod.LoadMesh(MeshData, path);
}

CylinderMeshComponent::CylinderMeshComponent()
{

}

void CylinderMeshComponent::CreateMesh(MeshRenderData& MeshData, float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
	//�뾶���
	float RadiusInterval = (InTopRadius - InBottomRadius) / InHeightSubdivision;
	//�߶ȼ��
	float HeightInterval = InHeight / InHeightSubdivision;

	float BetaValue = XM_2PI / (float)InAxialSubdivision;

	for (uint32_t i = 0; i < InHeightSubdivision; ++i)
	{
		float Y = 0.5f * InHeight - HeightInterval * i;
		float Radius = InTopRadius + i * RadiusInterval;
		for (size_t j = 0; j <= InAxialSubdivision; ++j)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					Radius * cosf(j * BetaValue),//x
					Y,//y
					Radius * sinf(j * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}
	}

	float VertexCircleNum = InAxialSubdivision + 1;

	//������Χ
	for (uint32_t i = 0; i < InHeightSubdivision; ++i)
	{
		for (uint32_t j = 0; j < InAxialSubdivision; ++j)
		{
			//���ǻ��Ƶ����ı���
			// 
			// ����Զ�������
			//������1
			//MeshData.IndexData.push_back(i * VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1 )* VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j+1);

			////������2
			//MeshData.IndexData.push_back(i * VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			//MeshData.IndexData.push_back(i * VertexCircleNum + j + 1);

			// ���߳����Լ�
			//������1
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j);
			MeshData.IndexData.push_back(i * VertexCircleNum + j);

			//������2
			MeshData.IndexData.push_back(i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(i * VertexCircleNum + j);
		}
	}

	//��������
	if (1)
	{
		uint32_t Index = MeshData.VertexData.size();

		float Y = 0.5f * InHeight;
		for (uint32_t i = 0; i <= InAxialSubdivision; ++i)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					InTopRadius * cosf(i * BetaValue),//x
					Y,//y
					InTopRadius * sinf(i * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}

		//����е�
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//����indexģ��
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < InAxialSubdivision; ++i)
		{
			MeshData.IndexData.push_back(CenterPoint);
			MeshData.IndexData.push_back(Index + i + 1);
			MeshData.IndexData.push_back(Index + i);
		}
	}

	//�����ײ�
	if (1)
	{
		uint32_t Index = MeshData.VertexData.size();

		float Y = -0.5f * InHeight;
		for (uint32_t i = 0; i <= InAxialSubdivision; ++i)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					InBottomRadius * cosf(i * BetaValue),//x
					Y,//y
					InBottomRadius * sinf(i * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}

		//����е�
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//����indexģ��
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < InAxialSubdivision; ++i)
		{
			MeshData.IndexData.push_back(CenterPoint);
			MeshData.IndexData.push_back(Index + i);
			MeshData.IndexData.push_back(Index + i + 1);
		}
	}
}

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

SphereMeshComponent::SphereMeshComponent()
{

}

void SphereMeshComponent::CreateMesh(MeshRenderData& MeshData, float InRadius, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
	float ThetaValue = XM_2PI / InHeightSubdivision;
	float BetaValue = XM_PI / InAxialSubdivision;

	//��Ӷ���
	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, InRadius, 0.f), XMFLOAT4(Colors::Red),
		XMFLOAT3(0.0f, 1.0f, 0.0f)));

	for (uint32_t i = 1; i < InAxialSubdivision; ++i)
	{
		float Beta = i * BetaValue;

		for (uint32_t j = 0; j <= InHeightSubdivision; ++j)
		{
			float Theta = j * ThetaValue;

			//��������תΪ�ѿ�������
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					InRadius * sinf(Beta) * cosf(Theta),//x
					InRadius * cosf(Beta),//y
					InRadius * sinf(Beta) * sinf(Theta)), //z
				XMFLOAT4(Colors::White)));

			int TopIndex = MeshData.VertexData.size() - 1;
			RVertex& InVertex = MeshData.VertexData[TopIndex];

			//�洢λ��
			XMVECTOR Pos = XMLoadFloat3(&InVertex.Position);
			XMStoreFloat3(&InVertex.Normal, XMVector3Normalize(Pos));

			//U���������
			InVertex.TangentU.x = -InRadius * sinf(Beta) * sinf(Theta);
			InVertex.TangentU.y = 0.f;
			InVertex.TangentU.z = InRadius * sinf(Beta) * cosf(Theta);

			//�洢����
			XMVECTOR Tangent = XMLoadFloat3(&InVertex.TangentU);
			XMStoreFloat3(&InVertex.TangentU, XMVector3Normalize(Tangent));
		}
	}

	//��ӵײ�
	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, -InRadius, 0.f), XMFLOAT4(Colors::Red),
		XMFLOAT3(0.0f, -1.0f, 0.0f)));

	//���Ʊ���
	for (uint32_t Index = 0; Index <= InAxialSubdivision; ++Index)
	{
		MeshData.IndexData.push_back(0);
		MeshData.IndexData.push_back(Index + 1);
		MeshData.IndexData.push_back(Index);
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
