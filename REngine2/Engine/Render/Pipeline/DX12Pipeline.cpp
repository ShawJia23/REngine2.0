#include"DX12Pipeline.h"
#include"../../Component/Mesh/MeshComponent.h"
#include"../../LoadAsset/Texture.h"
#include"../DX12/d3dx12.h"

DX12Pipeline::DX12Pipeline()
{
}

DX12Pipeline::~DX12Pipeline()
{
}

void DX12Pipeline::Init() 
{
    m_GeometryMap.Init();
}

void DX12Pipeline::BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData)
{
    m_GeometryMap.BuildMesh(mesh, meshData);
}

void DX12Pipeline::BuildPipeline()
{
    m_GeometryMap.BuildGeometry();

    m_GeometryMap.BuildDescriptorHeap();

    m_GeometryMap.BuildConstantBufferView();

    m_PipelineState.ResetGPSDesc();

    char TextureNumBuff[10] = { 0 };
    D3D_SHADER_MACRO ShaderMacro[] =
    {
        "TEXTURE2D_MAP_NUM",_itoa(GetTextureManage()->GetTextureSize(),TextureNumBuff,10),
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

    m_RootSignature.BuildRootSignature(GetTextureManage()->GetTextureSize());
    m_PipelineState.BindRootSignature(m_RootSignature.GetRootSignature());

    m_PipelineState.Build();
}

void DX12Pipeline::UpdateCalculations(const ViewportInfo viewportInfo)
{
    m_GeometryMap.UpdateCalculations(viewportInfo);
}

void DX12Pipeline::Draw()
{
    SetRootSignature();

    m_GeometryMap.Draw();

    m_PipelineState.CaptureKeyboardKeys();
}

void DX12Pipeline::ResetCommandList() 
{
    m_PipelineState.ResetCommandList();
}

void DX12Pipeline::SetRootSignature()
{
    m_RootSignature.SetRootSignature();
}