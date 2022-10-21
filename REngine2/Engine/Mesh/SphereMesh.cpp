#include "SphereMesh.h"

void SphereMesh::Init()
{
	Super::Init();


}

void SphereMesh::BuildMesh(const MeshRenderData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void SphereMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void SphereMesh::CreateMesh(MeshRenderData& MeshData, float radius, uint32_t axialSub, uint32_t heightSub)
{
	float ThetaValue = XM_2PI / heightSub;
	float BetaValue = XM_PI / axialSub;

	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, radius, 0.f), XMFLOAT4(Colors::Red)));

	for (uint32_t i = 1; i < axialSub; ++i)
	{
		float Beta = i * BetaValue;

		for (uint32_t j = 0; j <= heightSub; ++j)
		{
			float Theta = j * ThetaValue;

			//球面坐标转为笛卡尔坐标
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					radius * sinf(Beta) * cosf(Theta),//x
					radius * cosf(Beta),//y
					radius * sinf(Beta) * sinf(Theta)), //z
				XMFLOAT4(Colors::White)));

			int TopIndex = MeshData.VertexData.size() - 1;

			XMVECTOR Pos = XMLoadFloat3(&MeshData.VertexData[TopIndex].Position);
			XMStoreFloat3(&MeshData.VertexData[TopIndex].Normal, XMVector3Normalize(Pos));
		}
	}

	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, -radius, 0.f), XMFLOAT4(Colors::Red)));

	//绘制北极
	for (uint32_t Index = 0; Index <=axialSub; ++Index)
	{
		MeshData.IndexData.push_back(0);
		MeshData.IndexData.push_back(Index + 1);
		MeshData.IndexData.push_back(Index);
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
	for (uint32_t Index = 0; Index <axialSub; ++Index)
	{
		MeshData.IndexData.push_back(SouthBaseIndex);
		MeshData.IndexData.push_back(BaseIndex + Index);
		MeshData.IndexData.push_back(BaseIndex + Index + 1);
	}
}
