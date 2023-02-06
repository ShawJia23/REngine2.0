#include "RenderConfig.h"

EngineRenderConfig* EngineRenderConfig::RenderConfig = nullptr;

EngineRenderConfig::EngineRenderConfig()
	:ScreenWidth(1920)
	, ScreenHeight(1080)
	, RefreshRate(60)
	, SwapChainCount(2)
{
}

EngineRenderConfig* EngineRenderConfig::GetRenderConfig()
{
	if (!RenderConfig)
	{
		RenderConfig = new EngineRenderConfig();
	}

	return RenderConfig;
}

void EngineRenderConfig::Destroy()
{
	if (RenderConfig)
	{
		delete RenderConfig;
		RenderConfig = nullptr;
	}
}
