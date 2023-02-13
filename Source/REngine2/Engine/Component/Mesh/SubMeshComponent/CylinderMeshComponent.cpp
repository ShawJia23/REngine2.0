#include"CylinderMeshComponent.h"
#include"../../../Mesh/MeshType.h"
CylinderMeshComponent::CylinderMeshComponent()
{

}

void CylinderMeshComponent::CreateMesh(MeshRenderData& MeshData, float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
	//半径间隔
	float RadiusInterval = (InTopRadius - InBottomRadius) / InHeightSubdivision;
	//高度间隔
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

	//绘制腰围
	for (uint32_t i = 0; i < InHeightSubdivision; ++i)
	{
		for (uint32_t j = 0; j < InAxialSubdivision; ++j)
		{
			//我们绘制的是四边形
			// 
			// 法线远离摄像机
			//三角形1
			//MeshData.IndexData.push_back(i * VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1 )* VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j+1);

			////三角形2
			//MeshData.IndexData.push_back(i * VertexCircleNum + j);
			//MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			//MeshData.IndexData.push_back(i * VertexCircleNum + j + 1);

			// 法线朝向自己
			//三角形1
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j);
			MeshData.IndexData.push_back(i * VertexCircleNum + j);

			//三角形2
			MeshData.IndexData.push_back(i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back((i + 1) * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(i * VertexCircleNum + j);
		}
	}

	//构建顶部
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

		//添加中点
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//绘制index模型
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < InAxialSubdivision; ++i)
		{
			MeshData.IndexData.push_back(CenterPoint);
			MeshData.IndexData.push_back(Index + i + 1);
			MeshData.IndexData.push_back(Index + i);
		}
	}

	//构建底部
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

		//添加中点
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//绘制index模型
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < InAxialSubdivision; ++i)
		{
			MeshData.IndexData.push_back(CenterPoint);
			MeshData.IndexData.push_back(Index + i);
			MeshData.IndexData.push_back(Index + i + 1);
		}
	}
}

void CylinderMeshComponent::BuildKey(size_t& outKey, float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub)
{
	std::hash<float> floatHash;
	std::hash<int> intHash;
	outKey = 3;
	outKey += floatHash(topRadius);
	outKey += floatHash(bottomRadius);
	outKey += floatHash(height);
	outKey += intHash(axialSub);
	outKey += intHash(heightSub);
}


