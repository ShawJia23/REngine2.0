#include "MeshManage.h"
#include "../BoxMesh.h"
#include "../ConeMesh.h"
#include "../CylinderMesh.h"
#include "../SphereMesh.h"
#include "../PlaneMesh.h"
#include"../../Config/RenderConfig.h"
#include"../../EngineMinimal.h"
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

BMesh* RMeshManage::CreateSphereMesh(float InRadius, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return CreateMesh<SphereMesh>(InRadius, InAxialSubdivision, InHeightSubdivision);
}

BMesh* RMeshManage::CreateBoxMesh(float InHeight, float InWidth, float InDepth)
{
    return CreateMesh<BoxMesh>(InHeight, InWidth, InDepth);
}

BMesh* RMeshManage::CreateConeMesh(float InRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return CreateMesh<ConeMesh>(InRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

BMesh* RMeshManage::CreateCylinderMesh(float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return CreateMesh<CylinderMesh>(InTopRadius, InBottomRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

BMesh* RMeshManage::CreatePlaneMesh(float InHeight, float InWidth, uint32_t InHeightSubdivide, uint32_t InWidthSubdivide)
{
    return CreateMesh<PlaneMesh>(InHeight, InWidth, InHeightSubdivide, InWidthSubdivide);
}

template<class T, typename ...ParamTypes>
T* RMeshManage::CreateMesh(ParamTypes && ...Params)
{
    T* MyMesh = new T();

    //提取模型资源
    MeshRenderData meshData;
    MyMesh->CreateMesh(meshData, forward<ParamTypes>(Params)...);

    MyMesh->Init();

    //构建mesh
    m_pipeline.BuildMesh(MyMesh, meshData);

    return MyMesh;
}