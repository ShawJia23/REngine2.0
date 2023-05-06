#pragma once
#include "RenderTarget.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(RRenderTargetDelegate, void, ComPtr<ID3D12Resource>&)

class RBufferRenderTarget :public RRenderTarget
{
	typedef RRenderTarget Super;

public:
	RRenderTargetDelegate RenderTargetDelegate;

	virtual void Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat);

public:
	RBufferRenderTarget();
	~RBufferRenderTarget();
protected:
	virtual void BuildRenderTargetMap();
	virtual void BuildSRVDescriptors();
	virtual void BuildRTVDescriptors();

};