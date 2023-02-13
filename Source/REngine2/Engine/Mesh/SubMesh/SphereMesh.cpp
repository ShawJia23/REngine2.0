#include"SphereMesh.h"
#include"../../Component/Mesh/SubMeshComponent/SphereMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
SphereMesh::SphereMesh()
{
	Rename("Sphere");
}

void SphereMesh::Init()
{
	Super::Init();
}

void SphereMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void SphereMesh::CreateMesh(float radius, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "SphereComponent";
	auto Tmp = CREATE_RENDER_DATA(SphereMeshComponent, radius, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

