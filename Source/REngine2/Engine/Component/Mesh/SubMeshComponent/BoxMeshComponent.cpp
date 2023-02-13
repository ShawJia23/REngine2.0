#include"BoxMeshComponent.h"
#include"../../../Mesh/MeshType.h"
BoxMeshComponent::BoxMeshComponent()
{

}

void BoxMeshComponent::CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, float InDepth)
{
	float CHeight = 0.5f * InHeight;
	float CWidth = 0.5f * InWidth;
	float CDepth = 0.5f * InDepth;

	//构建顶点
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, -CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, -CHeight, -CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, -CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(-CWidth, CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, CHeight, CDepth), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(CWidth, -CHeight, CDepth), XMFLOAT4(Colors::White)));

	//构建索引
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

void BoxMeshComponent::BuildKey(size_t& outKey, float height, float width, float depth)
{
	std::hash<float> floatHash;

	outKey = 1;
	outKey += floatHash(height);
	outKey += floatHash(width);
	outKey += floatHash(depth);
}

