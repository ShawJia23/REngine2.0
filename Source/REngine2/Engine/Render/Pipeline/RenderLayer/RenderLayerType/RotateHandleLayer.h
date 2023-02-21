#pragma once
#include"BaseRenderLayer.h"
class RotateHandleLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	RotateHandleLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};