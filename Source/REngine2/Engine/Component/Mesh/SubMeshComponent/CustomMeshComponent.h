#pragma once
#include"../StaticMeshComponent.h"
#include"CustomMeshComponent.CodeReflection.h"
class CustomMeshComponent :public RStaticMeshComponent
{
	CODEREFLECTION()
public:
	CustomMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, const string& name);
	bool LoadFBXFromBuff(MeshRenderData& MeshData, const string& inName);
	void BuildKey(size_t& outKey, const string& name);
};