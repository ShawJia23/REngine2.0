#include"RenderLayer.h"

OpaqueRenderLayer::OpaqueRenderLayer():RenderLayer()
{
	SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE);
}

void OpaqueRenderLayer::BuildShader(UINT TextureSize) 
{
    char TextureNumBuff[10] = { 0 };
    D3D_SHADER_MACRO ShaderMacro[] =
    {
        "TEXTURE2D_MAP_NUM",_itoa(TextureSize,TextureNumBuff,10),
        NULL,NULL,
    };

    m_VertexShader.BuildShaders(L"Shader/Default.hlsl", "VertexShaderMain", "vs_5_1", ShaderMacro);
    m_PixelShader.BuildShaders(L"Shader/Default.hlsl", "PixelShaderMain", "ps_5_1", ShaderMacro);
    m_PipelineState.BindShader(m_VertexShader, m_PixelShader);

    m_InputElementDesc =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
    m_PipelineState.BindInputLayout(m_InputElementDesc.data(), m_InputElementDesc.size());
}
