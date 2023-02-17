#pragma once
#include"../EngineMinimal.h"
class RComponent;
class GActorObject;
class RWorld;
class RRenderData;

struct CollisionResult
{
	CollisionResult();

	bool bHit;// «∑Ò√¸÷–

	fvector_3d Location;
	fvector_3d Normal;

	float Distance;
	float Time;

	RComponent* Component;
	GActorObject* Actor;

	std::weak_ptr<RRenderData> RenderData;
};

struct CollisionScene
{
	static bool RaycastSingle(
		RWorld* inWorld,
		const XMVECTOR& originPoint,
		const XMVECTOR& direction,
		const XMMATRIX& viewInverseMatrix,
		CollisionResult& outResult);

	static bool RaycastSingle(
		RWorld* InWorld,
		GActorObject* InSpecificObjects,
		const std::vector<RComponent*>& IgnoreComponents,
		const XMVECTOR& OriginPoint,
		const XMVECTOR& Direction,
		const XMMATRIX& ViewInverseMatrix,
		CollisionResult& OutResult);
};