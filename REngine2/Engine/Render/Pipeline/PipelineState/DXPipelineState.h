#pragma once
#include"../../../Shader/Shader.h"
#include"../../../Interface/DXDeviceInterface.h"
#include"../DX12PipelineType.h"
//提供渲染内容的接口
struct RDXPipelineState :public IDirectXDeviceInterface_Struct
{
public:
	RDXPipelineState();

	void ResetGPSDesc();
	void ResetCommandList();
	void ResetPSO(int PSOtype=0);
	void BindInputLayout(const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT size);
	void BindRootSignature(ID3D12RootSignature* rootSignature);
	void BindShader(const RShader& vertexShader, const RShader& pixelShader);
	void Build();
	void CreatePSO(int PSOType);
	void CaptureKeyboardKeys();

public:
	void SetFillMode(bool bWireframe);
	void SetRenderTarget(int Index, const D3D12_RENDER_TARGET_BLEND_DESC& InRenderTargetBlend);
	void SetRasterizerState(const CD3DX12_RASTERIZER_DESC& InRasterizerDesc);
	void SetDepthStencilState(const CD3DX12_DEPTH_STENCIL_DESC& InDepthStencilDesc);
private:
	unordered_map<int, ComPtr<ID3D12PipelineState>>  m_PSO;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_GPSDesc;

	RPipeLineType m_PipelineType;
};