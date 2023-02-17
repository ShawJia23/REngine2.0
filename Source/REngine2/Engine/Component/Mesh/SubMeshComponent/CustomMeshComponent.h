#pragma once
#include"../StaticMeshComponent.h"
#include"CustomMeshComponent.CodeReflection.h"
class CustomMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	CustomMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, const string& name);

	void BuildKey(size_t& outKey, const string& name);
};