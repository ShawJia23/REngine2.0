#pragma once
#include "../EngineMinimal.h"
#include"../Collision/CollisionSystem.h"

class RWorld;
struct RayCastSystem
{
	//获得射线的数据
	static bool GetRayParamByScreen(const fvector_2id& ScreenXY,
		XMVECTOR& OriginPoint,
		XMVECTOR& Direction,
		XMMATRIX& ViewInverseMatrix);

	//射线去判断相交
	static bool HitResultByScreen(int ScreenX, int ScreenY, CollisionResult& OutResult);

	static bool HitSpecificObjectsResultByScreen(
		GActorObject* InSpecificObjects,
		const std::vector<RComponent*>& IgnoreComponents,
		int ScreenX, int ScreenY, CollisionResult& OutResult);
};