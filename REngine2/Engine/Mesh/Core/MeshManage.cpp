#include "MeshManage.h"
#include"../../Config/RenderConfig.h"
#include"../../EngineMinimal.h"
#include"../../Component/Mesh/BaseMeshComponent.h"
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
    return CreateMeshComponent<SphereMeshComponent>(InRadius, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateBoxMeshComponent(float InHeight, float InWidth, float InDepth)
{
    return CreateMeshComponent<BoxMeshComponent>(InHeight, InWidth, InDepth);
}

RMeshComponent* RMeshManage::CreateConeMeshComponent(float InRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return CreateMeshComponent<ConeMeshComponent>(InRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreateCylinderMeshComponent(float InTopRadius, float InBottomRadius, float InHeight, uint32_t InAxialSubdivision, uint32_t InHeightSubdivision)
{
    return CreateMeshComponent<CylinderMeshComponent>(InTopRadius, InBottomRadius, InHeight, InAxialSubdivision, InHeightSubdivision);
}

RMeshComponent* RMeshManage::CreatePlaneMeshComponent(float InHeight, float InWidth, uint32_t InHeightSubdivide, uint32_t InWidthSubdivide)
{
    return CreateMeshComponent<PlaneMeshComponent>(InHeight, InWidth, InHeightSubdivide, InWidthSubdivide);
}

RMeshComponent* RMeshManage::CreateCustomMeshComponent(string path)
{
    return CreateMeshComponent<CustomMeshComponent>(path);
}


template<class T, typename ...ParamTypes>
T* RMeshManage::CreateMeshComponent(ParamTypes && ...Params)
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