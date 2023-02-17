#include "CollisionSystem.h"
#include"../Render/Pipeline/Geometry/GeometryMap.h"
#include"../Component/Mesh/MeshComponent.h"
#include"../Camera/Camera.h"
#include"../World.h"
#include"../Render/Pipeline/DX12Pipeline.h"

CollisionResult::CollisionResult()
	:bHit(false)
	, Distance(0.f)
	, Time(0.f)
	, Component(NULL)
	, Actor(NULL)
{
}

bool CollisionScene::RaycastSingle(RWorld* inWorld, 
	const XMVECTOR& originPoint,
	const XMVECTOR& direction, 
	const XMMATRIX& viewInverseMatrix,
	CollisionResult& outResult)
{
	float FinalTime = FLT_MAX;
	float BoundTime = 0.f;
	float dis = FLT_MAX;
	auto renderDatas = inWorld->GetCamera()->GetRenderPipeline()->GetGeometryMap().GetRGeometry(0).RenderDatasPool;
	for (size_t i = 0; i < renderDatas.size(); i++)
	{
		std::shared_ptr<RRenderData>& pRenderData = renderDatas[i];
		if (!pRenderData->RenderData || !pRenderData->Mesh)
			continue;
		//点击点和射线转为模型空间做相交，在世界空间太费劲
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

		if (!pRenderData->Bounds.Intersects(LocalOriginPoint, LocalDirection, BoundTime))
			continue;
		if (BoundTime <= 0.f || BoundTime > FinalTime)
			continue;

		auto oPos= pRenderData->Mesh->GetPosition();
		auto cPos = inWorld->GetCamera()->GetPosition();
		float a = abs(cPos.x - oPos.x);
		float b = abs(cPos.y - oPos.y);
		float c = abs(cPos.z - oPos.z);
		float tempDis = a * a + b * b + c * c;

		//包围盒相交之后判断三角形
		UINT TriangleNumber = pRenderData->IndexSize / 3;
		float TriangleFinalTime = FLT_MAX;
		for (UINT j = 0; j < TriangleNumber; j++)
		{
			fvector_3id Indices;
			Indices.x = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + j * 3 + 0];
			Indices.y = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + j * 3 + 1];
			Indices.z = pRenderData->RenderData->IndexData[pRenderData->IndexOffsetPosition + j * 3 + 2];

			
			XMVECTOR Vertex0 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.x].Position);
			XMVECTOR Vertex1 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.y].Position);
			XMVECTOR Vertex2 = XMLoadFloat3(&pRenderData->RenderData->VertexData[Indices.z].Position);

			float TriangleTestsTime = 0.f;
			if (!TriangleTests::Intersects(LocalOriginPoint, LocalDirection, Vertex0, Vertex1, Vertex2, TriangleTestsTime))
				continue;
			if (TriangleTestsTime < 0 || TriangleTestsTime>FinalTime)
				continue;
			
			TriangleFinalTime = TriangleTestsTime;
			if (tempDis > dis)
				continue;
			dis = tempDis;
			
			outResult.bHit = true;
			outResult.Component = pRenderData->Mesh;
			outResult.Time = TriangleTestsTime;
			outResult.Actor = dynamic_cast<GActorObject*>(pRenderData->Mesh->GetOuter());
			outResult.RenderData = pRenderData;
		}
	}

	return false;
}

bool CollisionScene::RaycastSingle(
	RWorld* InWorld,
	GActorObject* InSpecificObjects,
	const std::vector<RComponent*>& IgnoreComponents,
	const XMVECTOR& OriginPoint,
	const XMVECTOR& Direction,
	const XMMATRIX& ViewInverseMatrix,
	CollisionResult& OutResult)
{
	return true;
}


