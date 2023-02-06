#pragma once
#include"BaseRenderLayer.h"

class OpaqueLayer :public RenderLayer
{
	typedef RenderLayer Super ;
public:
	OpaqueLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};

class SkyLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	SkyLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};

class SelectLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	SelectLayer();

	virtual void BuildShader();
	virtual void BuildPSO();
};