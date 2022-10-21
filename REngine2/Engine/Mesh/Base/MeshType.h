#pragma once
#include "../../EngineMinimal.h"
#include"../../Math/RMath.h"

struct RVertex
{
	RVertex(const XMFLOAT3& pos, const XMFLOAT4& color);
	RVertex(const XMFLOAT3& pos, const XMFLOAT4& color,const XMFLOAT3& normal);

	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT3 Normal;
};

struct MeshRenderData
{
	vector<RVertex> VertexData;
	vector<uint16_t> IndexData;

public:
	UINT GetVertexSizeInBytes() { return VertexData.size() * sizeof(RVertex); }
	UINT GetIndexSizeInBytes() { return IndexData.size() * sizeof(uint16_t); }
};

