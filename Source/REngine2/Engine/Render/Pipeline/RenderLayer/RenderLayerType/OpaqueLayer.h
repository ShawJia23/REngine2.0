#pragma once
#include"BaseRenderLayer.h"
class OpaqueLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	OpaqueLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};
