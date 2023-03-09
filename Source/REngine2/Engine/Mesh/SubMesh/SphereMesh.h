#pragma once
#include "../BaseMesh.h"
#include"SphereMesh.CodeReflection.h"
class SphereMesh :public BMesh
{
	CODEREFLECTION()
public:
	SphereMesh();

	virtual void Init();

	virtual void Draw(GameTimer& gt);

	void CreateMesh(float radius, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};