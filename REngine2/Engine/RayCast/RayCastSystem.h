#pragma once
#include "../EngineMinimal.h"
#include"../Collision/CollisionSystem.h"

class RWorld;
struct RayCastSystem
{
	static bool HitResultByScreen(RWorld* inWorld, int screenX, int screenY, CollisionResult& outResult);
};