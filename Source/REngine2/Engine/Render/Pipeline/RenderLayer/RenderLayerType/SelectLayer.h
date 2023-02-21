#pragma once
#include"BaseRenderLayer.h"
class SelectLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	SelectLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};