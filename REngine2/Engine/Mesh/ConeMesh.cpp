#include "ConeMesh.h"

void ConeMesh::Init()
{
	Super::Init();


}

void ConeMesh::BuildMesh(const MeshRenderData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void ConeMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void ConeMesh::CreateMesh(MeshRenderData& MeshData,float radius, float height, uint32_t axialSub, uint32_t heightSub)
{
	//半径间隔
	float RadiusInterval = -radius / (float)heightSub;
	//高度间隔
	float HeightInterval = height / (float)heightSub;

	float BetaValue = XM_2PI / (float)axialSub;

	//构建顶部
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 0.5f * height, 0.f), XMFLOAT4(Colors::White)));

	uint32_t Index = MeshData.VertexData.size();

	for (uint32_t i = 0; i < heightSub; ++i)
	{
		float Y = 0.5f * height - HeightInterval * i;
		float Radius = i * RadiusInterval;
		for (uint32_t j = 0; j <= axialSub; ++j)
		{
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					Radius * cosf(j * BetaValue),//x
					Y,//y
					Radius * sinf(j * BetaValue)), //z
				XMFLOAT4(Colors::White)));
		}
	}

	//添加中点
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, -0.5f * height, 0.f), XMFLOAT4(Colors::White)));

	//绘制index模型
	for (uint32_t i = 0; i < axialSub; ++i)
	{
		MeshData.IndexData.push_back(0);
		MeshData.IndexData.push_back(i + 1);
		MeshData.IndexData.push_back(i);
	}

	float BaseIndex = 1;
	float VertexCircleNum = axialSub + 1;
	//绘制腰围
	for (uint32_t i = 0; i < heightSub - 2; ++i)
	{
		for (uint32_t j = 0; j < axialSub; ++j)
		{
			//我们绘制的是四边形
			//三角形1
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j);
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j);
			//三角形2
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j);
			MeshData.IndexData.push_back(BaseIndex + i * VertexCircleNum + j + 1);
			MeshData.IndexData.push_back(BaseIndex + (i + 1) * VertexCircleNum + j + 1);
		}
	}

	//绘制南极
	uint32_t SouthBaseIndex = MeshData.VertexData.size() - 1;
	BaseIndex = SouthBaseIndex - VertexCircleNum;
	for (uint32_t Index = 0; Index < axialSub; ++Index)
	{
		MeshData.IndexData.push_back(SouthBaseIndex);
		MeshData.IndexData.push_back(BaseIndex + Index);
		MeshData.IndexData.push_back(BaseIndex + Index + 1);
	}
}
