#pragma once

#include "Base/Mesh.h"

class BoxMesh :public BMesh
{
	typedef BMesh Super;
public:
	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void Draw(float DeltaTime);

	static BoxMesh* CreateMesh();
};