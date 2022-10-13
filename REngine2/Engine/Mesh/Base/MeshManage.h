#pragma once
#include"Mesh.h"
#include"../../Core/ViewPort/ViewportInfo.h"
#include"../../Interface/DXDeviceInterface.h"
#include"../../Core/RObject/RMinimalObject.h"
#include"../../Render/Render.h"
#include"../../EngineMinimal.h"
#include"../../Render/Pipeline/DX12Pipeline.h"

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
	BMesh* CreateBoxMesh(
		float InHeight,
		float InWidth,
		float InDepth);

	BMesh* CreateConeMesh(
		float InRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	BMesh* CreateCylinderMesh(
		float InTopRadius,
		float InBottomRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);

	BMesh* CreatePlaneMesh(
		float InHeight,
		float InWidth,
		uint32_t InHeightSubdivide,
		uint32_t InWidthSubdivide);

	BMesh* CreateSphereMesh(
		float InRadius,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);


protected:
	template<class T, typename ...ParamTypes>
	T* CreateMesh(ParamTypes &&...Params);

protected:

	DX12Pipeline m_pipeline;

};