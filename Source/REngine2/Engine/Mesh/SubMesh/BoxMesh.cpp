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
void BoxMesh::Draw(GameTimer& gt)
{
	Super::Draw(gt);
}
void  BoxMesh::CreateMesh(float height, float width, float depth, EMeshRenderLayerType type)
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT("BoxComponent", GetTransformationComponent(), this);
	auto Tmp = CREATE_RENDER_DATA(BoxMeshComponent, height, width, depth);
	SetMeshComponent(Tmp);
}
