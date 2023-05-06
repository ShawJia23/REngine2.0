#include"RenderTarget.h"

RRenderTarget::RRenderTarget()
	:Width(256)
	, Height(256)
	, Format(DXGI_FORMAT_R8G8B8A8_UNORM)
{
	ResetViewport(Width, Height);
	ResetScissorRect(Width, Height);
}

RRenderTarget::~RRenderTarget() 
{

}

void RRenderTarget::Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat)
{
	Width = inWidth;
	Height = inHeight;
	Format = inFormat;

	ResetViewport(Width, Height);
	ResetScissorRect(Width, Height);

	BuildRenderTargetMap();

	BuildSRVDescriptors();
	BuildRTVDescriptors();
}

void RRenderTarget::ResetRenderTarget(UINT inWidth, UINT inHeight)
{
	if (inWidth != Width || inHeight != Height)
	{
		Width = inWidth;
		Height = inHeight;

		BuildRenderTargetMap();

		BuildSRVDescriptors();
		BuildRTVDescriptors();
	}
}

void RRenderTarget::ResetViewport(UINT inWidth, UINT inHeight)
{
	Viewport =
	{
		0.0f,//TopLeftX
		0.0f,//TopLeftY
		(float)inWidth,//Width
		(float)inHeight,//Height
		0.0f,//MinDepth
		1.0f //MaxDepth
	};
}

void RRenderTarget::ResetScissorRect(UINT InWidth, UINT InHeight)
{
	ScissorRect =
	{
		0,//left
		0,//top
		(LONG)InWidth,//right
		(LONG)InHeight//bottom
	};
}
