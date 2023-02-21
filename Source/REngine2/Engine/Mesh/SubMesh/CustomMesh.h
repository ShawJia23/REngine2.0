#pragma once
#include "../BaseMesh.h"
#include"PlaneMesh.CodeReflection.h"
class CustomMesh :public BMesh
{
	CODEREFLECTION()
public:
	CustomMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(string name,EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};