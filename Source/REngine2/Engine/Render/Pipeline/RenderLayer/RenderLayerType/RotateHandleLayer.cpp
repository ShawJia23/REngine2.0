#include"RotateHandleLayer.h"
#include"../../../../Shader/ShaderMacro.h"
RotateHandleLayer::RotateHandleLayer() :RenderLayer()
{
    SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPERATION_HANDLE_ROTATE);
}

void RotateHandleLayer::BuildShader()
{
    vector<RShaderMacro> ShaderMacro;
    BuildShaderMacro(ShaderMacro);

    vector<D3D_SHADER_MACRO> D3DShaderMacro;
    R2D3DShaderMacro(ShaderMacro, D3DShaderMacro);

    m_VertexShader.BuildShaders(L"Shader/OperationRotPlaneHandle.hlsl", "VertexShaderMain", "vs_5_1", D3DShaderMacro.data());
    m_PixelShader.BuildShaders(L"Shader/OperationRotPlaneHandle.hlsl", "PixelShaderMain", "ps_5_1", D3DShaderMacro.data());
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

void RotateHandleLayer::BuildPSO()
{
    Super::BuildPSO();


    //Í¸Ã÷
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

    CD3DX12_RASTERIZER_DESC RasterizerDesc(D3D12_DEFAULT);
    RasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
    RasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
    m_PipelineState->SetRasterizerState(RasterizerDesc);

    CD3DX12_DEPTH_STENCIL_DESC DepthStencilDesc = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    DepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS;
    m_PipelineState->SetDepthStencilState(DepthStencilDesc);

    m_PipelineState->CreatePSO((int)GetRenderLayerType());
}