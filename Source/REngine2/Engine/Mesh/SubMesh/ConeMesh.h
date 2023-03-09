#pragma once
#include "../BaseMesh.h"
#include"ConeMesh.CodeReflection.h"
class ConeMesh :public BMesh
{
	CODEREFLECTION()
public:
	ConeMesh();

	virtual void Init();

	virtual void Draw(GameTimer& gt);

	void CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};