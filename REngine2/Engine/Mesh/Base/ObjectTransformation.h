#pragma once
#include "MeshType.h"

struct RObjectTransformation
{
	RObjectTransformation();

	XMFLOAT4X4 World;

	static XMFLOAT4X4 IdentityMatrix4x4();
};
