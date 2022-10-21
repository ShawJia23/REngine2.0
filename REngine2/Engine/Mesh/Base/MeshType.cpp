#include "MeshType.h"

RVertex::RVertex(const XMFLOAT3& pos, const XMFLOAT4& color)
	:Position(pos)
	, Color(color)
{

}
RVertex::RVertex(const XMFLOAT3& pos, const XMFLOAT4& color, const XMFLOAT3& normal)
	:Position(pos)
	, Color(color)
	,Normal(normal)
{

}

