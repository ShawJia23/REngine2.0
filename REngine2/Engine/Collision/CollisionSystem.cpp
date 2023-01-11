#include "CollisionSystem.h"
#include"../Render/Pipeline/Geometry/GeometryMap.h"
#include"../Component/Mesh/BaseMeshComponent.h"
#include"../Camera/Camera.h"
#include"../Core/World.h"
bool CollisionScene::RaycastSingle(RWorld* inWorld, const XMVECTOR& originPoint, 
	const XMVECTOR& direction, const XMMATRIX& viewInverseMatrix, 
	CollisionResult& outResult)
{
	float FinalTime = FLT_MAX;
	float BoundTime = 0.f;
	auto renderDatas = inWorld->GetCamera()->GetRenderPipeline()->GetGeometryMap().GetRGeometry(0).RenderDatasPool;
	for (size_t i = 0; i < renderDatas.size(); i++)
	{
		std::shared_ptr<RRenderData>& pRenderData = renderDatas[i];

		//תģ�;ֲ�
		XMMATRIX WorldMatrix = XMLoadFloat4x4(&pRenderData->WorldMatrix);
		XMVECTOR WorldMatrixDeterminant = XMMatrixDeterminant(WorldMatrix);
		XMMATRIX WorldMatrixInverse = XMMatrixInverse(&WorldMatrixDeterminant, WorldMatrix);

		//�ֲ�����
		XMMATRIX LocalMatrix = XMMatrixMultiply(viewInverseMatrix, WorldMatrixInverse);

		//�ֲ��ռ�����ߵ�λ��
		XMVECTOR LocalOriginPoint = XMVector3TransformCoord(originPoint, LocalMatrix);
		XMVECTOR LocalDirection = XMVector3TransformNormal(direction, LocalMatrix);

		//��λ��
		LocalDirection = XMVector3Normalize(LocalDirection);


		if (pRenderData->Bounds.Intersects(LocalOriginPoint, LocalDirection, BoundTime))
		{
			auto cPos=inWorld->GetCamera()->GetPosition();
			if (BoundTime > 0.f && BoundTime < FinalTime)
			{
				FinalTime = BoundTime;
				if (pRenderData->RenderData)
				{
					outResult.bHit = true;
					outResult.Component = pRenderData->Mesh;
					outResult.Time = BoundTime;
					if (pRenderData->Mesh)
					{
						outResult.Actor = dynamic_cast<GActorObject*>(pRenderData->Mesh->GetOuter());
					}

					//�õ���Ⱦ����
					outResult.RenderData = pRenderData;
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
