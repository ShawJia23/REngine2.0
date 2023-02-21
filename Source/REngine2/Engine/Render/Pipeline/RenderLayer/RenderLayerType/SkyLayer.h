#pragma once
#include"BaseRenderLayer.h"
class SkyLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	SkyLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};