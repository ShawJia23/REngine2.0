#include"RenderLayer.h"

OpaqueLayer::OpaqueLayer():RenderLayer()
{
	SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE);
}

void OpaqueLayer::BuildShader(UINT TextureSize) 
{
    char TextureNumBuff[10] = { 0 };
    D3D_SHADER_MACRO ShaderMacro[] =
    {
        "TEXTURE2D_MAP_NUM",_itoa(TextureSize,TextureNumBuff,10),
        NULL,NULL,
    };

    m_VertexShader.BuildShaders(L"Shader/Default.hlsl", "VertexShaderMain", "vs_5_1", ShaderMacro);
    m_PixelShader.BuildShaders(L"Shader/Default.hlsl", "PixelShaderMain", "ps_5_1", ShaderMacro);
    m_PipelineState->BindShader(m_VertexShader, m_PixelShader);

    m_InputElementDesc =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
    m_PipelineState->BindInputLayout(m_InputElementDesc.data(), m_InputElementDesc.size());
}

void OpaqueLayer::BuildPSO(UINT size)
{
    Super::BuildPSO(size);

    m_PipelineState->CreatePSO((int)GetRenderLayerType());
}

SkyLayer::SkyLayer() :RenderLayer()
{
    SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_CUBEMAP);
}

void SkyLayer::BuildShader(UINT TextureSize)
{
    char TextureNumBuff[10] = { 0 };
    D3D_SHADER_MACRO ShaderMacro[] =
    {
        "TEXTURE2D_MAP_NUM",_itoa(TextureSize,TextureNumBuff,10),
        //"CUBE_MAP_NUM",_itoa(GeometryMap->GetDrawCubeMapResourcesNumber(),TextureNumBuff,10),
        NULL,NULL,
    };

    m_VertexShader.BuildShaders(L"Shader/Sky.hlsl", "VertexShaderMain", "vs_5_1", ShaderMacro);
    m_PixelShader.BuildShaders(L"Shader/Sky.hlsl", "PixelShaderMain", "ps_5_1", ShaderMacro);
    m_PipelineState->BindShader(m_VertexShader, m_PixelShader);

    m_InputElementDesc =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
    m_PipelineState->BindInputLayout(m_InputElementDesc.data(), m_InputElementDesc.size());
}

void SkyLayer::BuildPSO(UINT size)
{
    Super::BuildPSO(size);

    CD3DX12_RASTERIZER_DESC RasterizerDesc(D3D12_DEFAULT);
    RasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
    RasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
    m_PipelineState->SetRasterizerState(RasterizerDesc);

    CD3DX12_DEPTH_STENCIL_DESC DepthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    DepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    m_PipelineState->SetDepthStencilState(DepthStencilDesc);

    m_PipelineState->CreatePSO((int)GetRenderLayerType());
}