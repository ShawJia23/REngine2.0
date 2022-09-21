#include "CylinderMesh.h"

void CylinderMesh::Init()
{
	Super::Init();


}

void CylinderMesh::BuildMesh(const MeshRenderingData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void CylinderMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void CylinderMesh::CreateMesh(MeshRenderingData& MeshData, float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub)
{
	//半径间隔
	float RadiusInterval = (topRadius - bottomRadius) / heightSub;
	//高度间隔
	float HeightInterval = height / heightSub;

	float BetaValue = XM_2PI / (float)axialSub;

	for (uint32_t i = 0; i < heightSub; ++i)
	{
		float Y = 0.5f * height - HeightInterval * i;
		float Radius = topRadius + i * RadiusInterval;
		for (size_t j = 0; j <= axialSub; ++j)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					Radius * cosf(j * BetaValue),//x
					Y,//y
					Radius * sinf(j * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}
	}

	float VertexCircleNum = axialSub + 1;

	//绘制腰围
	for (uint32_t i = 0; i < heightSub; ++i)
	{
		for (uint32_t j = 0; j < axialSub; ++j)
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

		float Y = 0.5f * height;
		for (uint32_t i = 0; i <= axialSub; ++i)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					topRadius * cosf(i * BetaValue),//x
					Y,//y
					topRadius * sinf(i * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}

		//添加中点
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//绘制index模型
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < axialSub; ++i)
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

		float Y = -0.5f * height;
		for (uint32_t i = 0; i <= axialSub; ++i)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					bottomRadius * cosf(i * BetaValue),//x
					Y,//y
					bottomRadius * sinf(i * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}

		//添加中点
		MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, Y, 0.f), XMFLOAT4(Colors::White)));

		//绘制index模型
		float CenterPoint = MeshData.VertexData.size() - 1;
		for (uint32_t i = 0; i < axialSub; ++i)
		{
			MeshData.IndexData.push_back(CenterPoint);
			MeshData.IndexData.push_back(Index + i);
			MeshData.IndexData.push_back(Index + i + 1);
		}
	}
}
