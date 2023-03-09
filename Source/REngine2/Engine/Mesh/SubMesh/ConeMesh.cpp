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

void ConeMesh::Draw(GameTimer& gt)
{
	Super::Draw(gt);
}

void ConeMesh::CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT("ConeComponent", GetTransformationComponent(), this);
	auto Tmp = CREATE_RENDER_DATA(ConeMeshComponent, radius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}
