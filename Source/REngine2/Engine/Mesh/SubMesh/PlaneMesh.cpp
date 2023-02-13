#include"PlaneMesh.h"
#include"../../Component/Mesh/SubMeshComponent/PlaneMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
PlaneMesh::PlaneMesh()
{
	Rename("Plane");
}

void PlaneMesh::Init()
{
	Super::Init();
}

void PlaneMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void PlaneMesh::CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub, EMeshRenderLayerType type)
{
	CreateObjectParam inObjectParam;
	inObjectParam.Outer = this;
	inObjectParam.Name = "PlaneComponent";
	auto Tmp = CREATE_RENDER_DATA(PlaneMeshComponent, height, width, heightSub, widthSub);
	SetMeshComponent(Tmp);
}

