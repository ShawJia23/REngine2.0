#pragma once
#include"RenderLayer.h"

class RenderLayerManage 
{
public:
	RenderLayerManage();
	void ResetCommandList();
	void BuildPipelineState(UINT TextureSize, ID3D12RootSignature* rootSignature);
	void CaptureKeyboardKeys();
private:
	std::vector<RenderLayer> m_RenderLayers;
};