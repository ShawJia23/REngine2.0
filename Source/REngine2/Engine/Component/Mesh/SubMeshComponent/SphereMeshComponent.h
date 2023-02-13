#pragma once
#include"../StaticMeshComponent.h"
#include"SphereMeshComponent.CodeReflection.h"
class SphereMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	SphereMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InRadius,
		uint32_t InAxialSubdivision, uint32_t InHeightSubdivision);

	void BuildKey(size_t& outKey, float radius, uint32_t axialSub, uint32_t heightSub);
};