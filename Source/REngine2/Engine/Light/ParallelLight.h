#pragma once
#include"Light.h"
#include"ParallelLight.CodeReflection.h"
class GParallelLight :public GLight
{
	CODEREFLECTION()
public:
	GParallelLight();

	virtual void Tick(GameTimer& gt);

	RVARIABLE(CodeType = Resources, Category = Light, Draggable)
	fvector_3d RotateSpeed;
};