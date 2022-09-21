#include "PlaneMesh.h"

void PlaneMesh::Init()
{
	Super::Init();
}

void PlaneMesh::BuildMesh(const MeshRenderingData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void PlaneMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void PlaneMesh::CreateMesh(MeshRenderingData& MeshData, float height, float width, uint32_t heightSub, uint32_t widthSub)
{
	auto SubdivideValue = [&](float InValue, uint32_t InSubdivideValue)->float
	{
		if (InSubdivideValue <= 1)
		{
			return InValue;
		}

		return InValue / ((float)InSubdivideValue - 1);
	};

	float CHeight = 0.5f * height;
	float CWidth = 0.5f * width;

	float heightSubValue = SubdivideValue(height, heightSub);
	float widthSubValue = SubdivideValue(width, widthSub);

	//绘制点的位置
	for (uint32_t i = 0; i < heightSub; ++i)
	{
		float Z = CHeight - i * heightSubValue;
		for (uint32_t j = 0; j < widthSub; ++j)
		{
			float X = CWidth - j * widthSubValue;
			MeshData.VertexData.push_back(RVertex(
				XMFLOAT3(
					X,//x
					0.f,//y
					Z), //z
				XMFLOAT4(Colors::White)));
		}
	}

	//绘制index
	for (uint32_t i = 0; i < heightSub - 1; ++i)
	{
		for (uint32_t j = 0; j < widthSub - 1; ++j)
		{
			////我们绘制的是四边形
			////三角形1
			//MeshData.IndexData.push_back( i * widthSub + j);
			//MeshData.IndexData.push_back( i * widthSub + j + 1);
			//MeshData.IndexData.push_back( (i + 1) * widthSub + j);

			////三角形2
			//MeshData.IndexData.push_back( (i + 1) * widthSub + j);
			//MeshData.IndexData.push_back( i * widthSub + j + 1);
			//MeshData.IndexData.push_back( (i + 1) * widthSub + j + 1);

			//我们绘制的是四边形
			//三角形1
			MeshData.IndexData.push_back((i + 1) * widthSub + j);
			MeshData.IndexData.push_back(i * widthSub + j + 1);
			MeshData.IndexData.push_back(i * widthSub + j);

			//三角形2
			MeshData.IndexData.push_back((i + 1) * widthSub + j + 1);
			MeshData.IndexData.push_back(i * widthSub + j + 1);
			MeshData.IndexData.push_back((i + 1) * widthSub + j);
		}
	}
}
