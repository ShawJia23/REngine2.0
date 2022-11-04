#include"RenderMeshData.h"
#include"../../../Mesh/Core/MeshType.h"
RRenderData::RRenderData()
	: IndexSize(0)
	, VertexSize(0)
	, IndexOffsetPosition(0)
	, VertexOffsetPosition(0)
	, VertexTypeSize(sizeof(RVertex))
	, IndexTypeSize(sizeof(uint16_t))
	, IndexFormat(DXGI_FORMAT_R16_UINT)
	, WorldMatrix(RMath::IdentityMatrix4x4())
	, Mesh(NULL)
{

}
