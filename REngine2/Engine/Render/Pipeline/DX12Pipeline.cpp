#include"DX12Pipeline.h"
#include"../../Component/Mesh/MeshComponent.h"
#include"../../Manage/TextureManage.h"
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
    m_PipelineState.ResetGPSDesc();

    m_GeometryMap.SetPipelineState(&m_PipelineState);

    m_GeometryMap.BuildGeometry();

    m_GeometryMap.BuildDescriptorHeap();


    m_UIPipeline.Init(
        m_GeometryMap.GetHeap(),
        m_GeometryMap.GetDesptorSize());//ShadowCubeMap

    m_GeometryMap.BuildConstantBufferView();

    m_RootSignature.BuildRootSignature(GetTextureManage()->GetTextureSize());

    m_PipelineState.BindRootSignature(m_RootSignature.GetRootSignature());

    m_GeometryMap.BuildPSO();
}

void DX12Pipeline::UpdateCalculations(const ViewportInfo viewportInfo)
{
    m_GeometryMap.UpdateCalculations(viewportInfo);
}

void DX12Pipeline::Draw(float DeltaTime)
{
    SetRootSignature();

    m_PipelineState.CaptureKeyboardKeys();

    m_GeometryMap.Draw();

    m_UIPipeline.Draw(DeltaTime);
}

void DX12Pipeline::ResetCommandList() 
{
    m_PipelineState.ResetCommandList();
}

void DX12Pipeline::SetRootSignature()
{
    m_RootSignature.SetRootSignature();
}