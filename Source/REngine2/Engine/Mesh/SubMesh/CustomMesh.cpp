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
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "CustomComponent";
	auto Tmp = CREATE_RENDER_DATA(CustomMeshComponent, name);
	SetMeshComponent(Tmp);
}

