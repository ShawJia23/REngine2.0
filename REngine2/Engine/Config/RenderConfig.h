#pragma once

struct EngineRenderConfig
{
	EngineRenderConfig();

	int ScrrenWidth;
	int ScrrenHight;
	int RefreshRate;
	int SwapChainCount;

	static EngineRenderConfig* GetRenderConfig();
	static void Destroy();
private:
	static EngineRenderConfig* RenderConfig;
};