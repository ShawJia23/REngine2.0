#include"SelectLayer.h"
#include"../../../../Shader/ShaderMacro.h"

SelectLayer::SelectLayer()
{
    SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_SELECT);
}

void SelectLayer::BuildShader()
{
    vector<RShaderMacro> ShaderMacro;
    BuildShaderMacro(ShaderMacro);

    vector<D3D_SHADER_MACRO> D3DShaderMacro;
    R2D3DShaderMacro(ShaderMacro, D3DShaderMacro);
    wstring pStr = PathHelper::GetEngineShadersPath() + L"/SelectShadow.hlsl";
    m_VertexShader.BuildShaders(pStr, "VertexShaderMain", "vs_5_1", D3DShaderMacro.data());
    m_PixelShader.BuildShaders(pStr, "PixelShaderMain", "ps_5_1", D3DShaderMacro.data());
    m_PipelineState->BindShader(m_VertexShader, m_PixelShader);

    m_InputElementDesc =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
    };
    m_PipelineState->BindInputLayout(m_InputElementDesc.data(), m_InputElementDesc.size());
}

void SelectLayer::BuildPSO()
{
    Super::BuildPSO();

    D3D12_RENDER_TARGET_BLEND_DESC RenderTargetBlendDesc;
    RenderTargetBlendDesc.BlendEnable = true;
    RenderTargetBlendDesc.LogicOpEnable = false;

    RenderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
    RenderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

    RenderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
    RenderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;//F(1,1,1)
    RenderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;//F(0,0,0)
    RenderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;

    RenderTargetBlendDesc.LogicOp = D3D12_LOGIC_OP_NOOP;
    RenderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

    m_PipelineState->SetRenderTarget(0, RenderTargetBlendDesc);

    m_PipelineState->CreatePSO((int)GetRenderLayerType());
}