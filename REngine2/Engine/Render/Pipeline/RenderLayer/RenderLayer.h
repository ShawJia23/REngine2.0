#pragma once
#include"BaseRenderLayer.h"

class OpaqueRenderLayer :public RenderLayer
{
	typedef RenderLayer Super ;
public:
	OpaqueRenderLayer();

	virtual void BuildShader(UINT TextureSize);
};