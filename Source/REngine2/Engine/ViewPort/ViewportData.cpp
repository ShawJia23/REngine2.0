#include "ViewportData.h"
#include"../Config/RenderConfig.h"

RViewportData::RViewportData()
	:Width(EngineRenderConfig::GetRenderConfig()->ScreenWidth)
	, Height(EngineRenderConfig::GetRenderConfig()->ScreenHeight)
	, YFOV(0.25f * XM_PI)
	, Aspect((float)Width / (float)Height)
	, ZNear(0.1f)
	, ZFar(10000.f)
{

}

void RViewportData::ResetSize(int width, int height)
{
	Width = width;
	Height = height;

	Aspect = (float)width / (float)height;
}
