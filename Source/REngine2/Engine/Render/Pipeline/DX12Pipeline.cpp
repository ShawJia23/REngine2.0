#include"DX12Pipeline.h"
#include"../../Component/Mesh/MeshComponent.h"
#include"../../Manage/TextureManage.h"
#include"../DX12/d3dx12.h"
#include"../Engine/DXRenderEngine.h"

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

void DX12Pipeline::BuildMesh(const size_t meshHash,RMeshComponent* mesh, const MeshRenderData& meshData)
{
    m_GeometryMap.BuildMesh(meshHash,mesh, meshData);
}

void DX12Pipeline::BuildPipeline()
{
    m_PipelineState.ResetGPSDesc();

    m_GeometryMap.InitRenderLayer(&m_PipelineState);

    m_GeometryMap.BuildGeometry();

    m_GeometryMap.BuildDynamicReflectionMesh();

    m_GeometryMap.BuildDescriptorHeap();

    m_UIPipeline.Init(
        m_GeometryMap.GetHeap(),
        m_GeometryMap.GetDesptorSize());

    m_GeometryMap.BuildConstantBufferView();

    //构建动态的CubeMap
    m_DynamicCubeMap.Init(
        &m_GeometryMap,
        &m_PipelineState,GetRenderLayer().get());


    //texture=0时构建根签名和shader会报错
    m_RootSignature.BuildRootSignature(RTextureManage::getInstance().GetTextureSize());

    m_PipelineState.BindRootSignature(m_RootSignature.GetRootSignature());

    m_DynamicCubeMap.BuildViewport(fvector_3d(0,0,0));
    //构建RTVDes
    m_DynamicCubeMap.BuildRenderTargetDescriptor();

    //构建深度模板
    m_DynamicCubeMap.BuildDepthStencil();

    m_GeometryMap.BuildPSO();
}

void DX12Pipeline::UpdateCalculations(const ViewportInfo viewportInfo)
{
    m_DynamicCubeMap.UpdateCalculations(viewportInfo);
    m_GeometryMap.UpdateCalculations(viewportInfo);
}

void DX12Pipeline::Draw(GameTimer& gt)
{
    SetRootSignature();

    m_PipelineState.CaptureKeyboardKeys();

    m_GeometryMap.Draw();

    m_DynamicCubeMap.PreDraw();

    m_UIPipeline.Draw(gt);
}

void DX12Pipeline::PostDraw(GameTimer& gt) 
{
    m_GeometryMap.PostDraw(gt);
}

void DX12Pipeline::OnResetSize(int width, int height)
{
    m_GeometryMap.OnResetSize(width, height);
}

bool DX12Pipeline::FindMeshRenderingDataByHash(const size_t& inHash, std::shared_ptr<RRenderData>& meshData, int renderLayerIndex)
{
    return m_GeometryMap.FindMeshRenderingDataByHash(inHash, meshData, renderLayerIndex);
}

void DX12Pipeline::DuplicateMesh(RMeshComponent* mesh, std::shared_ptr<RRenderData>& meshData)
{
    m_GeometryMap.DuplicateMesh(mesh, meshData);
}

void DX12Pipeline::ResetCommandList() 
{
    m_PipelineState.ResetCommandList();
}

void DX12Pipeline::SetRootSignature()
{
    m_RootSignature.SetRootSignature();
}