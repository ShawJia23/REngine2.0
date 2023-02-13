#pragma once
#include"../StaticMeshComponent.h"
#include"CylinderMeshComponent.CodeReflection.h"
class CylinderMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	CylinderMeshComponent();

	void CreateMesh(
		MeshRenderData& MeshData,
		float InTopRadius,
		float InBottomRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	void BuildKey(size_t& outKey, float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub);
};