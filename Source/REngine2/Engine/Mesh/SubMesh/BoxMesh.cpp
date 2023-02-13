#include"BoxMesh.h"
#include"../../Component/Mesh/SubMeshComponent/BoxMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
BoxMesh::BoxMesh()
{
	Rename("Box");
}
void BoxMesh::Init()
{
	Super::Init();
}
void BoxMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}
void  BoxMesh::CreateMesh(float height, float width, float depth, EMeshRenderLayerType type)
{
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "BoxComponent";
	auto Tmp = CREATE_RENDER_DATA(BoxMeshComponent, height, width, depth);
	SetMeshComponent(Tmp);
}
