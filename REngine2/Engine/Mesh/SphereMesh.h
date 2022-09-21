#pragma once

#include "Base/Mesh.h"

class SphereMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void Draw(float DeltaTime);

	void CreateMesh(MeshRenderingData& MeshData, float radius, uint32_t axialSub, uint32_t heightSub);
};