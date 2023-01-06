#include "CollisionSystem.h"
#include"../Render/Pipeline/Geometry/GeometryMap.h"
bool CollisionScene::RaycastSingle(RWorld* inWorld, const XMVECTOR& originPoint, const XMVECTOR& direction, const XMMATRIX& viewInverseMatrix, CollisionResult& outResult)
{
	float FinalTime = FLT_MAX;
	for (size_t i = 0; i < RGeometry::RenderingDatas.size(); i++)
	{
		std::shared_ptr<RRenderData>& pRenderingData = RGeometry::RenderingDatas[i];

		//转模型局部
		XMMATRIX WorldMatrix = XMLoadFloat4x4(&pRenderingData->WorldMatrix);
		XMVECTOR WorldMatrixDeterminant = XMMatrixDeterminant(WorldMatrix);
		XMMATRIX WorldMatrixInverse = XMMatrixInverse(&WorldMatrixDeterminant, WorldMatrix);

		//局部矩阵
		XMMATRIX LocalMatrix = XMMatrixMultiply(viewInverseMatrix, WorldMatrixInverse);

		//局部空间的射线点位置
		XMVECTOR LocalOriginPoint = XMVector3TransformCoord(originPoint, LocalMatrix);
		XMVECTOR LocalDirection = XMVector3TransformNormal(direction, LocalMatrix);

		//单位化
		LocalDirection = XMVector3Normalize(LocalDirection);

		//射线是否可以和AABB相交
		float BoundTime = 0.f;
		float TriangleTime = 0.f;
		if (pRenderingData->Bounds.Intersects(LocalOriginPoint, LocalDirection, BoundTime))
		{
			if (BoundTime < FinalTime)
			{
				if (pRenderingData->MeshRenderingData)
				{
					UINT TriangleNumber = pRenderingData->IndexSize / 3;
					for (UINT i = 0; i < TriangleNumber; i++)
					{
						fvector_3id Indices;
						Indices.x = pRenderingData->MeshRenderingData->IndexData[pRenderingData->IndexOffsetPosition + i * 3 + 0];
						Indices.y = pRenderingData->MeshRenderingData->IndexData[pRenderingData->IndexOffsetPosition + i * 3 + 1];
						Indices.z = pRenderingData->MeshRenderingData->IndexData[pRenderingData->IndexOffsetPosition + i * 3 + 2];

						XMVECTOR Vertex0 = XMLoadFloat3(&pRenderingData->MeshRenderingData->VertexData[Indices.x].Position);
						XMVECTOR Vertex1 = XMLoadFloat3(&pRenderingData->MeshRenderingData->VertexData[Indices.y].Position);
						XMVECTOR Vertex2 = XMLoadFloat3(&pRenderingData->MeshRenderingData->VertexData[Indices.z].Position);

						float TriangleTestsTime = 0.f;
						if (TriangleTests::Intersects(LocalOriginPoint, LocalDirection, Vertex0, Vertex1, Vertex2, TriangleTestsTime))
						{
							FinalTime = BoundTime;
							if (TriangleTestsTime < TriangleTime)
							{
								TriangleTime = TriangleTestsTime;

								OutResult.bHit = true;
								OutResult.Component = pRenderingData->Mesh;
								OutResult.Time = TriangleTestsTime;
								if (pRenderingData->Mesh)
								{
									OutResult.Actor = dynamic_cast<GActorObject*>(pRenderingData->Mesh->GetOuter());
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}
