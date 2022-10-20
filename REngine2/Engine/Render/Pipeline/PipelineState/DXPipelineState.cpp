#include"DXPipelineState.h"
#include"../../../Platform/Windows/WindowsEngine.h"
#include"../../Engine/RenderEngine.h"
#include"../DX12PipelineType.h"
RDXPipelineState::RDXPipelineState()
{
    m_PSO.insert(pair<int, ComPtr<ID3D12PipelineState>>(1, ComPtr<ID3D12PipelineState>()));
    m_PSO.insert(pair<int, ComPtr<ID3D12PipelineState>>(2, ComPtr<ID3D12PipelineState>()));

    m_PipelineType = RPipeLineType::Wireframe;
}

void RDXPipelineState::ResetGPSDesc()
{
    memset(&m_GPSDesc, 0, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
}

void RDXPipelineState::ResetCommandList()
{
    GetCommandList()->Reset(GetCommandAllocator().Get(), m_PSO[(int)m_PipelineType].Get());
}

void RDXPipelineState::BindInputLayout(const D3D12_INPUT_ELEMENT_DESC* inputElementDescs, UINT size)
{
    m_GPSDesc.InputLayout.pInputElementDescs = inputElementDescs;
    m_GPSDesc.InputLayout.NumElements = size;
}

void RDXPipelineState::BindRootSignature(ID3D12RootSignature* rootSignature)
{
    m_GPSDesc.pRootSignature = rootSignature;
}

void RDXPipelineState::BindShader(const RShader& vertexShader, const RShader& pixelShader)
{
    m_GPSDesc.VS.pShaderBytecode = reinterpret_cast<BYTE*>(vertexShader.GetBufferPointer());
    m_GPSDesc.VS.BytecodeLength = vertexShader .GetBufferSize();

    m_GPSDesc.PS.pShaderBytecode = pixelShader.GetBufferPointer();
    m_GPSDesc.PS.BytecodeLength = pixelShader.GetBufferSize();
}

void RDXPipelineState::Build()
{
    m_GPSDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    m_GPSDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;//以线框方式显示
    m_GPSDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;

    m_GPSDesc.SampleMask = UINT_MAX;

    m_GPSDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    m_GPSDesc.NumRenderTargets = 1;

    m_GPSDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    m_GPSDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

    m_GPSDesc.SampleDesc.Count = GetEngine()->GetRenderEngine()->GetDXGISampleCount();
    m_GPSDesc.SampleDesc.Quality = GetEngine()->GetRenderEngine()->GetDXGISampleQuality();

    m_GPSDesc.RTVFormats[0] = GetEngine()->GetRenderEngine()->GetBackBufferFormat();
    m_GPSDesc.DSVFormat = GetEngine()->GetRenderEngine()->GetDepthStencilFormat();

    //线框模型注册
    ANALYSIS_HRESULT(GetD3dDevice()->CreateGraphicsPipelineState(&m_GPSDesc, IID_PPV_ARGS(&m_PSO[(int)Wireframe])));
        //实体模型注册
    m_GPSDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;//以实体方式显示
    ANALYSIS_HRESULT(GetD3dDevice()->CreateGraphicsPipelineState(&m_GPSDesc, IID_PPV_ARGS(&m_PSO[(int)GrayModel])));
}


void RDXPipelineState::CaptureKeyboardKeys()
{
    if (GetAsyncKeyState('1') & 0x8000)
    {
        m_PipelineType = RPipeLineType::Wireframe;
    }
    else if (GetAsyncKeyState('2') & 0x8000)
    {
        m_PipelineType = RPipeLineType::GrayModel;
    }
}