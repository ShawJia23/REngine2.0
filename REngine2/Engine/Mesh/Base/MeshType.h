#pragma once
#include "../../EngineMinimal.h"
#include"../../Math/RMath.h"

struct RVertex
{
	RVertex(const XMFLOAT3& InPos, const XMFLOAT4& InColor);

	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT3 Normal;
};

struct MeshRenderingData
{
	vector<RVertex> VertexData;
	vector<uint16_t> IndexData;
};

