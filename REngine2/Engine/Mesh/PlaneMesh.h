#pragma once

#include "Base/Mesh.h"

class PlaneMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void BuildMesh(const MeshRenderData* InRenderingData);

	virtual void Draw(float DeltaTime);

	void CreateMesh(MeshRenderData& MeshData, float height, float width, uint32_t heightSub, uint32_t widthSub);
};