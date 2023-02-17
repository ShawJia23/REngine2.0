#pragma once
#include "../EngineMinimal.h"
#include"../Collision/CollisionSystem.h"

class RWorld;
struct RayCastSystem
{
	//������ߵ�����
	static bool GetRayParamByScreen(RWorld* inWorld,
		const fvector_2id& ScreenXY,
		XMVECTOR& OriginPoint,
		XMVECTOR& Direction,
		XMMATRIX& ViewInverseMatrix);

	//����ȥ�ж��ཻ
	static bool HitResultByScreen(RWorld* InWorld, int ScreenX, int ScreenY, CollisionResult& OutResult);

	static bool HitSpecificObjectsResultByScreen(
		RWorld* InWorld,
		GActorObject* InSpecificObjects,
		const std::vector<RComponent*>& IgnoreComponents,
		int ScreenX, int ScreenY, CollisionResult& OutResult);
};