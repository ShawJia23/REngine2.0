#pragma once
#include "../BaseMesh.h"
#include"PlaneMesh.CodeReflection.h"
class PlaneMesh :public BMesh
{
	CODEREFLECTION()
public:
	PlaneMesh();

	virtual void Init();

	virtual void Draw(GameTimer& gt);

	void CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub, EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};