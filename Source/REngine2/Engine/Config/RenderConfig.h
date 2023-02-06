#pragma once

struct EngineRenderConfig
{
	EngineRenderConfig();

	int ScreenWidth;
	int ScreenHeight;
	int RefreshRate;
	int SwapChainCount;

	static EngineRenderConfig* GetRenderConfig();
	static void Destroy();
private:
	static EngineRenderConfig* RenderConfig;
};