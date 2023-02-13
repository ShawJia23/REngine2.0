#include"ConeMesh.h"
#include"../../Component/Mesh/SubMeshComponent/ConeMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
ConeMesh::ConeMesh()
{
	Rename("Cone");
}

void ConeMesh::Init()
{
	Super::Init();
}

void ConeMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void ConeMesh::CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "ConeComponent";
	auto Tmp = CREATE_RENDER_DATA(ConeMeshComponent, radius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}
