#include"BufferRenderTarget.h"


RBufferRenderTarget::RBufferRenderTarget()
	:Super()
{

}

RBufferRenderTarget::~RBufferRenderTarget()
{

}

void RBufferRenderTarget::Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat)
{
	Super::Init(inWidth, inHeight, inFormat);
}

void RBufferRenderTarget::BuildRenderTargetMap()
{
	if (RenderTargetDelegate.IsBound())
	{
		RenderTargetDelegate.Execute(RenderTargetMap);
	}
}

void RBufferRenderTarget::BuildSRVDescriptors()
{

}

void RBufferRenderTarget::BuildRTVDescriptors()
{

}
