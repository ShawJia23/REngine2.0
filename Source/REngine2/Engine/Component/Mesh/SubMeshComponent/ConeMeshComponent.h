#pragma once
#include"../StaticMeshComponent.h"
#include"ConeMeshComponent.CodeReflection.h"
class ConeMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	ConeMeshComponent();

	void CreateMesh(
		MeshRenderData& MeshData,
		float InRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	void BuildKey(size_t& outKey, float radius, float height, uint32_t axialSub, uint32_t heightSub);
};