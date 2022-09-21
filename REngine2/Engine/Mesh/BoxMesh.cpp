#include "BoxMesh.h"

void BoxMesh::Init()
{
	Super::Init();


}

void BoxMesh::BuildMesh(const MeshRenderingData* InRenderingData)
{
	Super::BuildMesh(InRenderingData);


}

void BoxMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);


}

void  BoxMesh::CreateMesh(MeshRenderingData& MeshData,float height, float width, float depth)
{
	MeshRenderingData MeshData;

	float pHeight = 0.5f * height;
	float pWidth = 0.5f * width;
	float pDepth = 0.5f * depth;

	//构建我们的顶点
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(pWidth,- pHeight, -pDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(pWidth, pHeight, -pDepth), XMFLOAT4(Colors::AliceBlue)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-pWidth, pHeight, -pDepth), XMFLOAT4(Colors::Aqua)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-pWidth, -pHeight, -pDepth), XMFLOAT4(Colors::Aquamarine)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(pWidth, -pHeight, pDepth), XMFLOAT4(Colors::Bisque)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(pWidth, pHeight, pDepth), XMFLOAT4(Colors::Blue)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-pWidth, pHeight, pDepth), XMFLOAT4(Colors::Chocolate)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-pWidth, -pHeight, pDepth), XMFLOAT4(Colors::Chocolate)));

	//构建我们的索引
	//前
	MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(2);
	MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(2); MeshData.IndexData.push_back(3);

	//后
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(5);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(7); MeshData.IndexData.push_back(6);

	//左
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(5); MeshData.IndexData.push_back(1);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(0);

	//右
	MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(2); MeshData.IndexData.push_back(6);
	MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(7);

	//上
	MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(5); MeshData.IndexData.push_back(6);
	MeshData.IndexData.push_back(1); MeshData.IndexData.push_back(6); MeshData.IndexData.push_back(2);

	//下
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(0); MeshData.IndexData.push_back(3);
	MeshData.IndexData.push_back(4); MeshData.IndexData.push_back(3); MeshData.IndexData.push_back(7);
}
