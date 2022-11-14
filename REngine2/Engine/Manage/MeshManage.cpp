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
    m_pipeline.Draw();
}

void RMeshManage::PreDraw(float DeltaTime)
{
    m_pipeline.ResetCommandList();
}

RMeshComponent* RMeshManage::CreateSphereMeshComponent(float InRadius, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<SphereMeshComponent>(this, InRadius, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateBoxMeshComponent(float InHeight, float InWidth, float InDepth)
{
    return MeshConstruction::CreateMeshComponent<BoxMeshComponent>(this, InHeight, InWidth, InDepth);
}

RMeshComponent* RMeshManage::CreateConeMeshComponent(float InRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<ConeMeshComponent>(this, InRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateCylinderMeshComponent(float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<CylinderMeshComponent>(this, InTopRadius, InBottomRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreatePlaneMeshComponent(float InHeight, float InWidth, uint32_t InHeightSubdivide, uint32_t InWidthSubdivide)
{
    return MeshConstruction::CreateMeshComponent<PlaneMeshComponent>(this, InHeight, InWidth, InHeightSubdivide, InWidthSubdivide);
}

RMeshComponent* RMeshManage::CreateCustomMeshComponent()
{
    return MeshConstruction::CreateMeshComponent<CustomMeshComponent>(this, 0);
}

void RMeshManage::CreateMeshGroup(RMeshComponent* mesh, const MeshRenderData& meshData)
{
    m_pipeline.BuildMesh(mesh, meshData);
}