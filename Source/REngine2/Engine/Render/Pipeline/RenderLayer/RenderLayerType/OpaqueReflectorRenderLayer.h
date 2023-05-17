#pragma once
#include"BaseRenderLayer.h"

class OpaqueReflectorRenderLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	OpaqueReflectorRenderLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};