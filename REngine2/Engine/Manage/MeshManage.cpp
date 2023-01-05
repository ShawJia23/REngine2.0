#include "MeshManage.h"
#include"../Config/RenderConfig.h"
#include"../EngineMinimal.h"
#include"../Component/Mesh/BaseMeshComponent.h"
RMeshManage::RMeshManage()
{
}

void RMeshManage::Init()
{
    m_pipeline.Init();
}

void RMeshManage::BuildPipeline()
{
    m_pipeline.BuildPipeline();
}

void RMeshManage::UpdateCalculations(float DeltaTime, const ViewportInfo viewportInfo)
{
    m_pipeline.UpdateCalculations(viewportInfo);
}

void RMeshManage::PostDraw(float DeltaTime)
{
   
}

void RMeshManage::Draw(float DeltaTime)
{
    m_pipeline.Draw(DeltaTime);
}

void RMeshManage::PreDraw(float DeltaTime)
{
    m_pipeline.ResetCommandList();
}

RMeshComponent* RMeshManage::CreateSphereMeshComponent(float InRadius, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<SphereMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, InRadius, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateBoxMeshComponent(float InHeight, float InWidth, float InDepth)
{
    return MeshConstruction::CreateMeshComponent<BoxMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, InHeight, InWidth, InDepth);
}

RMeshComponent* RMeshManage::CreateConeMeshComponent(float InRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<ConeMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, InRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateCylinderMeshComponent(float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<CylinderMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, InTopRadius, InBottomRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreatePlaneMeshComponent(float InHeight, float InWidth, uint32_t InHeightSubdivide, uint32_t InWidthSubdivide)
{
    return MeshConstruction::CreateMeshComponent<PlaneMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, InHeight, InWidth, InHeightSubdivide, InWidthSubdivide);
}

RMeshComponent* RMeshManage::CreateCustomMeshComponent()
{
    return MeshConstruction::CreateMeshComponent<CustomMeshComponent>(this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, "name");
}

void RMeshManage::CreateMeshGroup(size_t hashKey, RMeshComponent* mesh, const MeshRenderData& meshData)
{
    m_pipeline.BuildMesh(hashKey,mesh, meshData);
}