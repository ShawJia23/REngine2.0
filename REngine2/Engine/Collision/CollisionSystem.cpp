#include "CollisionSystem.h"
#include"../Render/Pipeline/Geometry/GeometryMap.h"
#include"../Component/Mesh/BaseMeshComponent.h"
bool CollisionScene::RaycastSingle(RWorld* inWorld, const XMVECTOR& originPoint, const XMVECTOR& direction, const XMMATRIX& viewInverseMatrix, CollisionResult& outResult)
{
	float FinalTime = FLT_MAX;
	for (size_t i = 0; i < RGeometry::RenderingDatas.size(); i++)
	{
		std::shared_ptr<RRenderData>& pRenderData = RGeometry::RenderingDatas[i];

		//转模型局部
		XMMATRIX WorldMatrix = XMLoadFloat4x4(&pRenderData->WorldMatrix);
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
		if (pRenderData->Bounds.Intersects(LocalOriginPoint, LocalDirection, BoundTime))
		{ 
			if (BoundTime < FinalTime)
			{
				if (pRenderData->RenderData)
				{
					UINT TriangleNumber = pRenderData->IndexSize / 3;
					for (UINT i = 0; i < TriangleNumber; i++)
					{
						fvector_3id Indices;
						Indices.x = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + i * 3 + 0];
						Indices.y = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + i * 3 + 1];
						Indices.z = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + i * 3 + 2];

						XMVECTOR Vertex0 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.x].Position);
						XMVECTOR Vertex1 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.y].Position);
						XMVECTOR Vertex2 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.z].Position);

						float TriangleTestsTime = 0.f;
						if (TriangleTests::Intersects(LocalOriginPoint, LocalDirection, Vertex0, Vertex1, Vertex2, TriangleTestsTime))
						{
							FinalTime = BoundTime;
							if (TriangleTestsTime < TriangleTime)
							{
								TriangleTime = TriangleTestsTime;

								outResult.bHit = true;
								outResult.Component = pRenderData->Mesh;
								outResult.Time = TriangleTestsTime;
								if (pRenderData->Mesh)
								{
									outResult.Actor = dynamic_cast<GActorObject*>(pRenderData->Mesh->GetOuter());
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

CollisionResult::CollisionResult()
	:bHit(false)
	, Distance(0.f)
	, Time(0.f)
	, Component(NULL)
	, Actor(NULL)
{
}
