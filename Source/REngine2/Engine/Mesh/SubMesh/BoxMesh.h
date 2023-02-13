#pragma once
#include "../BaseMesh.h"
#include"BoxMesh.CodeReflection.h"

class BoxMesh : public BMesh
{
	CODEREFLECTION()
public:
	BoxMesh();
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float height, float width, float depth, EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};