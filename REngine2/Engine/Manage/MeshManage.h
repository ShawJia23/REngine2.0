#pragma once
#include"../Mesh/Mesh.h"
#include"../Core/ViewPort/ViewportInfo.h"
#include"../Interface/DXDeviceInterface.h"
#include"../Core/RObject/RMinimalObject.h"
#include"../Render/Render.h"
#include"../EngineMinimal.h"
#include"../Render/Pipeline/DX12Pipeline.h"

class RMeshComponent;
struct CreateObjectParam;
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
		const CreateObjectParam& inObjectParam,
		float inHeight,
		float inWidth,
		float inDepth);

	RMeshComponent* CreateConeMeshComponent(
		const CreateObjectParam& inObjectParam,
		float inRadius,
		float inHeight,
		uint32_t inAxialSubdivision,
		uint32_t inHeightSubdivision);

	RMeshComponent* CreateCylinderMeshComponent(
		const CreateObjectParam& inObjectParam,
		float inTopRadius,
		float inBottomRadius,
		float inHeight,
		uint32_t inAxialSubdivision,
		uint32_t inHeightSubdivision);

	RMeshComponent* CreatePlaneMeshComponent(
		const CreateObjectParam& inObjectParam,
		float inHeight,
		float inWidth,
		uint32_t inHeightSubdivide,
		uint32_t inWidthSubdivide);

	RMeshComponent* CreateSphereMeshComponent(
		const CreateObjectParam& inObjectParam,
		float inRadius,
		uint32_t inAxialSubdivision,
		uint32_t inHeightSubdivision);

	RMeshComponent* CreateCustomMeshComponent(const CreateObjectParam& inObjectParam);

	void CreateMeshGroup(size_t hashKey, RMeshComponent* mesh, const MeshRenderData& meshData);
	
	DX12Pipeline* GetDX12Pipeline() const { return const_cast<DX12Pipeline*>(&m_pipeline); }
protected:
	DX12Pipeline m_pipeline;

};