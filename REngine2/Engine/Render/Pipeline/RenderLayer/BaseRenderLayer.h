#pragma once
#include"RenderLayer.h"

class OpaqueRenderLayer :public RenderLayer
{
	typedef RenderLayer Super;
public:
	OpaqueRenderLayer();

	virtual void BuildShader(UINT TextureSize);

	virtual int GetRenderLayerType() const { return 0; }
};