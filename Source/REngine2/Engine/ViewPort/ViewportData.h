#pragma once

#include "../EngineMinimal.h"

class RViewportData
{
	friend class GClientViewport;

public:
	RViewportData();

	void ResetSize(int InWidth, int InHeight);

	int Width;
	int Height;

	float YFOV;
	float Aspect;
	float ZNear;
	float ZFar;
};