#include "MeshManage.h"
#include"../Config/RenderConfig.h"
#include"../EngineMinimal.h"
#include"../Component/Mesh/SubMeshComponent/BoxMeshComponent.h"
#include"../Component/Mesh/SubMeshComponent/PlaneMeshComponent.h"
#include"../Component/Mesh/SubMeshComponent/CylinderMeshComponent.h"
#include"../Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../Component/Mesh/SubMeshComponent/ConeMeshComponent.h"
#include"../Component/Mesh/SubMeshComponent/SphereMeshComponent.h"
#include"../Construction/MeshConstruction.h"
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

void RMeshManage::OnResetSize(int width, int height)
{
    m_pipeline.OnResetSize(width, height);
}

void RMeshManage::PostDraw(float DeltaTime)
{
    m_pipeline.PostDraw(DeltaTime);
}

void RMeshManage::Draw(float DeltaTime)
{
    m_pipeline.Draw(DeltaTime);
}

void RMeshManage::PreDraw(float DeltaTime)
{
    m_pipeline.ResetCommandList();
}

RMeshComponent* RMeshManage::CreateSphereMeshComponent(const CreateObjectParam& inObjectParam, float inRadius, uint32_t inAxialSubdivision, uint32_t inHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<SphereMeshComponent>(inObjectParam,this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, inRadius, inAxialSubdivision, inHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateBoxMeshComponent(const CreateObjectParam& inObjectParam, float inHeight, float inWidth, float inDepth)
{
    return MeshConstruction::CreateMeshComponent<BoxMeshComponent>(inObjectParam,this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, inHeight, inWidth, inDepth);
}

RMeshComponent* RMeshManage::CreateConeMeshComponent(const CreateObjectParam& inObjectParam, float inRadius, float inHeight, uint32_t inAxialSubdivision, uint32_t inHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<ConeMeshComponent>(inObjectParam, this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, inRadius, inHeight, inAxialSubdivision, inHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateCylinderMeshComponent(const CreateObjectParam& inObjectParam, float inTopRadius, float inBottomRadius, float inHeight, uint32_t inAxialSubdivision, uint32_t inHeightSubdivision)
{
    return MeshConstruction::CreateMeshComponent<CylinderMeshComponent>(inObjectParam, this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, inTopRadius, inBottomRadius, inHeight, inAxialSubdivision, inHeightSubdivision);
}

RMeshComponent* RMeshManage::CreatePlaneMeshComponent(const CreateObjectParam& inObjectParam, float inHeight, float inWidth, uint32_t inHeightSubdivide, uint32_t inWidthSubdivide)
{
    return MeshConstruction::CreateMeshComponent<PlaneMeshComponent>(inObjectParam, this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, inHeight, inWidth, inHeightSubdivide, inWidthSubdivide);
}

RMeshComponent* RMeshManage::CreateCustomMeshComponent(const CreateObjectParam& inObjectParam)
{
    return MeshConstruction::CreateMeshComponent<CustomMeshComponent>(inObjectParam, this, EMeshRenderLayerType::RENDERLAYER_OPAQUE, "name");
}

void RMeshManage::CreateMeshGroup(size_t hashKey, RMeshComponent* mesh, const MeshRenderData& meshData)
{
    m_pipeline.BuildMesh(hashKey,mesh, meshData);
}