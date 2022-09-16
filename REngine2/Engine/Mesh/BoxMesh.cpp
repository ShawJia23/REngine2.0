#include "BoxMesh.h"
#include "Base/MeshType.h"

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

BoxMesh* BoxMesh::CreateMesh()
{
	MeshRenderingData MeshData;

	//�������ǵĶ���
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT4(Colors::White)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 1.f, 0.f), XMFLOAT4(Colors::AliceBlue)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(1.f, 1.f, 0.f), XMFLOAT4(Colors::Aqua)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(1.f, 0.f, 0.f), XMFLOAT4(Colors::Aquamarine)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 0.f, 1.f), XMFLOAT4(Colors::Bisque)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(0.f, 1.f, 1.f), XMFLOAT4(Colors::Blue)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(1.f, 1.f, 1.f), XMFLOAT4(Colors::Chocolate)));
	MeshData.VertexData.push_back(RVertex(XMFLOAT3(1.f, 0.f, 1.f), XMFLOAT4(Colors::Chocolate)));

	//�������ǵ�����
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

	BoxMesh* boxMesh = new BoxMesh;
	boxMesh->BuildMesh(&MeshData);

	boxMesh->Init();

	return boxMesh;
}
