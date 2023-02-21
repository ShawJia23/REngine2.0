#pragma once
#include"BaseRenderLayer.h"
class PositionHandleLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	PositionHandleLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};