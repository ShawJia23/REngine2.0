#pragma once
#include"../../../Shader/Shader.h"
#include"../PipelineState/DXPipelineState.h"
class RenderLayer 
{
public:
	RenderLayer();
	void ResetCommandList();
	void BuildPipelineState(UINT TextureSize, ID3D12RootSignature* rootSignature);
	void CaptureKeyboardKeys();

	virtual void BuildShader(UINT TextureSize);
	virtual int GetRenderLayerType() const { return RenderLayerType; }
private:
	RShader m_VertexShader;
	RShader m_PixelShader;
	vector<D3D12_INPUT_ELEMENT_DESC> m_InputElementDesc;
	RDXPipelineState m_PipelineState;

	int RenderLayerType;
};