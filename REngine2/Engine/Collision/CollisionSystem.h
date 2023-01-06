#pragma once
#include"../EngineMinimal.h"
class RComponent;
class GActorObject;
class RWorld;

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
};

struct CollisionScene
{
	static bool RaycastSingle(
		RWorld* inWorld,
		const XMVECTOR& originPoint,
		const XMVECTOR& direction,
		const XMMATRIX& viewInverseMatrix,
		CollisionResult& outResult);
};