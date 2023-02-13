#pragma once
#include"../StaticMeshComponent.h"
#include"PlaneMeshComponent.CodeReflection.h"
class PlaneMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	PlaneMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth,
		uint32_t InHeightSubdivide, uint32_t InWidthSubdivide);

	void BuildKey(size_t& outKey, float height, float width, uint32_t heightSub, uint32_t widthSub);
};