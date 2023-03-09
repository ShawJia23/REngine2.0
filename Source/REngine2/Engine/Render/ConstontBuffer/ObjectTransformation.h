#pragma once
#include "../../Mesh/MeshType.h"

struct RObjectTransformation
{
	RObjectTransformation();

	XMFLOAT4X4 World;
	XMFLOAT4X4 TextureTransformation;
	XMFLOAT4X4 NormalTransformation;
	UINT MaterialIndex;
	UINT VV1;
	UINT VV2;
	UINT VV3;
};
