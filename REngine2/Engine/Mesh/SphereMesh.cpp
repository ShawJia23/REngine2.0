#include "SphereMesh.h"

void SphereMesh::Init()
{
	Super::Init();


}

void SphereMesh::BuildMesh(const MeshRenderingData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void SphereMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void SphereMesh::CreateMesh(MeshRenderingData& MeshData, float radius, uint32_t axialSub, uint32_t heightSub)
{
	float thetaVal = XM_2PI / heightSub;
	float betaVal = XM_2PI / axialSub;

	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, radius, 0.f), XMFLOAT4(Colors::Red)));

	for (uint32_t i = 1; i < axialSub; ++i) 
	{
		float beta = i  * betaVal;
		for (uint32_t j= 0; j <=heightSub; ++j)
		{
			float theta = j  * thetaVal;

			MeshData.VertexData.push_back(RVertex(XMFLOAT3(radius * sinf(beta) * cosf(theta),
				radius * cosf(beta),
				radius * sinf(beta) * sinf(theta)), XMFLOAT4(Colors::White)));

			int topIndex = MeshData.VertexData.size() - 1;

			XMVECTOR Pos = XMLoadFloat3(&MeshData.VertexData[topIndex].Position);
			XMStoreFloat3(&MeshData.VertexData[topIndex].Normal, XMVector3Normalize(Pos));
		}
	}

	MeshData.VertexData.push_back(RVertex(
		XMFLOAT3(0.f, -radius, 0.f), XMFLOAT4(Colors::Red)));

	//绘制北极
	for (uint32_t i = 0; i < axialSub; ++i)
	{
		MeshData.IndexData.push_back(0);
		MeshData.IndexData.push_back(i + 1);
		MeshData.IndexData.push_back(i);
	}

	float baseIndex = 1;
	float vertexCircleNum = axialSub + 1;
	//绘制腰围
	for (uint32_t i = 0; i < heightSub - 2; ++i)
	{
		for (uint32_t j = 0; j < axialSub; ++j)
		{
			//绘制四边形
			//三角形1
			MeshData.IndexData.push_back(baseIndex + i * vertexCircleNum + j);
			MeshData.IndexData.push_back(baseIndex + i * vertexCircleNum + j + 1);
			MeshData.IndexData.push_back(baseIndex + (i + 1) * vertexCircleNum + j);
			//三角形2
			MeshData.IndexData.push_back(baseIndex + (i + 1) * vertexCircleNum + j);
			MeshData.IndexData.push_back(baseIndex + i * vertexCircleNum + j + 1);
			MeshData.IndexData.push_back(baseIndex + (i + 1) * vertexCircleNum + j + 1);
		}
	}

	//绘制南极
	uint32_t SouthBaseIndex = MeshData.VertexData.size() - 1;
	baseIndex = SouthBaseIndex - vertexCircleNum;
	for (uint32_t Index = 0; Index < axialSub; ++Index)
	{
		MeshData.IndexData.push_back(SouthBaseIndex);
		MeshData.IndexData.push_back(baseIndex + Index);
		MeshData.IndexData.push_back(baseIndex + Index + 1);
	}
}
