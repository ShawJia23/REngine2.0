#include"CylinderMesh.h"
#include"../../Component/Mesh/SubMeshComponent/CylinderMeshComponent.h"
#include"../../Construction/MacroConstruction.h"
CylinderMesh::CylinderMesh()
{
	Rename("Cylinder");
}

void CylinderMesh::Init()
{
	Super::Init();
}

void CylinderMesh::Draw(float DeltaTime)
{
	Super::Draw(DeltaTime);
}

void CylinderMesh::CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type)
{
	BUILD_OBJECT_PARAMETERS_BY_COMPONENT("CylinderComponent", GetTransformationComponent(), this);
	auto Tmp = CREATE_RENDER_DATA(CylinderMeshComponent, topRadius, bottomRadius, height, axialSub, heightSub);
	SetMeshComponent(Tmp);
}

