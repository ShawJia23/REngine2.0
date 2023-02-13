#pragma once
#include"../StaticMeshComponent.h"
#include"BoxMeshComponent.CodeReflection.h"
class BoxMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	BoxMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, float InDepth);

	void BuildKey(size_t& outKey, float height, float width, float depth);
};