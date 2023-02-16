#pragma once
#include"Light.h"
#include"ParallelLight.CodeReflection.h"
class GParallelLight :public GLight
{
	CODEREFLECTION()
public:
	GParallelLight();

	virtual void Tick(float DeltaTime);
};