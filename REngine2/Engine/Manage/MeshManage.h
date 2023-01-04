#pragma once
#include"../Mesh/Mesh.h"
#include"../Core/ViewPort/ViewportInfo.h"
#include"../Interface/DXDeviceInterface.h"
#include"../Core/RObject/RMinimalObject.h"
#include"../Render/Render.h"
#include"../EngineMinimal.h"
#include"../Render/Pipeline/DX12Pipeline.h"

class RMeshComponent;
class RMeshManage :public RMinimalObject, public IRenderingInterface,public IDirectXDeviceInterface
{
public:
	RMeshManage();

	virtual void Init();

	virtual void BuildPipeline();

	virtual void UpdateCalculations(float DeltaTime, const ViewportInfo viewportInfo);

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

public:
	RMeshComponent* CreateBoxMeshComponent(
		float InHeight,
		float InWidth,
		float InDepth);

	RMeshComponent* CreateConeMeshComponent(
		float InRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	RMeshComponent* CreateCylinderMeshComponent(
		float InTopRadius,
		float InBottomRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	RMeshComponent* CreatePlaneMeshComponent(
		float InHeight,
		float InWidth,
		uint32_t InHeightSubdivide,
		uint32_t InWidthSubdivide);

	RMeshComponent* CreateSphereMeshComponent(
		float InRadius,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	RMeshComponent* CreateCustomMeshComponent();

	void CreateMeshGroup(size_t hashKey, RMeshComponent* mesh, const MeshRenderData& meshData);
	
	DX12Pipeline& GetDX12Pipeline() { return m_pipeline; }
protected:
	DX12Pipeline m_pipeline;

};