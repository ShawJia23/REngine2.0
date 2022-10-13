#pragma once
#include"../../../Shader/Shader.h"
#include"../../../Interface/DXDeviceInterface.h"
//�ṩ��Ⱦ���ݵĽӿ�
struct RDXPipelineState :public IDirectXDeviceInterface_Struct
{
public:
	RDXPipelineState();

	void ResetGPSDesc();
	void ResetCommandList();
	void BindInputLayout(const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT size);
	void BindRootSignature(ID3D12RootSignature* rootSignature);
	void BindShader(const RShader& vertexShader, const RShader& pixelShader);
	void Build();

private:
	ComPtr<ID3D12PipelineState> m_PSO;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC m_GPSDesc;
};