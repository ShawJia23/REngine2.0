#pragma once
#include "../BaseMesh.h"
#include"PlaneMesh.CodeReflection.h"
class CylinderMesh :public BMesh
{
	CODEREFLECTION()
public:
	CylinderMesh();

	virtual void Init();

	virtual void Draw(GameTimer& gt);

	void CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub, EMeshRenderLayerType type = EMeshRenderLayerType::RENDERLAYER_OPAQUE);
};