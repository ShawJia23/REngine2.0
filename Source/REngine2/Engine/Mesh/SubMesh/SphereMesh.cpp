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

void SphereMesh::Draw(GameTimer& gt)
{
	Super::Draw(gt);
}

void SphereMesh::CreateMesh(float radius, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT(GetTransformationComponent(), this);
	auto Tmp = CREATE_RENDER_DATA(SphereMeshComponent, radius, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

