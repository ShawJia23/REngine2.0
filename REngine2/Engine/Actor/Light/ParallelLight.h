#pragma once
#include"../ActorObject.h"
#include"Light.h"

class GParallelLight :public GLight
{
	typedef GLight Super;
public:
	GParallelLight();

	virtual void Tick(float DeltaTime);
};