#pragma once
#include "Base/Mesh.h"

class CylinderMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void Draw(float DeltaTime);

	void CreateMesh(MeshRenderingData& MeshData, float topRadius,float bottomRadius,float height,uint32_t axialSub,uint32_t heightSub);
};