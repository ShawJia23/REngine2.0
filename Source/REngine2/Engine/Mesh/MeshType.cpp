#include "MeshType.h"

RVertex::RVertex():Position(0,0,0), Color(0,0,0,0), Normal(0,0,0), TangentU(0,0,0), TexC(0,0)
{

}

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

RVertex::RVertex(const XMFLOAT3& pos, const XMFLOAT3& normal, const XMFLOAT2& texC, const XMFLOAT4& color) 
	:Position(pos)
	, Normal(normal)
	,TexC(texC)
	, Color(color)
{

}
