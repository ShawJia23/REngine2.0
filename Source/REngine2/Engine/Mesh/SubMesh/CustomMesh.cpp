#include"CustomMesh.h"
#include"../../Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
CustomMesh::CustomMesh()
{
	Rename("Custom");
}

void CustomMesh::Init()
{
	Super::Init();
}

void CustomMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void CustomMesh::CreateMesh(string name,EMeshRenderLayerType type)
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT("CustomComponent", GetTransformationComponent(), this);
	auto Tmp = CREATE_RENDER_DATA(CustomMeshComponent, name);
	SetMeshComponent(Tmp);
}

