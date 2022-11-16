#pragma once
#include"BaseRenderLayer.h"

class OpaqueLayer :public RenderLayer
{
	typedef RenderLayer Super ;
public:
	OpaqueLayer();

	virtual void BuildShader(UINT TextureSize);
	virtual void BuildPSO(UINT size);
};

class SkyLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	SkyLayer();

	virtual void BuildShader(UINT TextureSize);
	virtual void BuildPSO(UINT size);
};