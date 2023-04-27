#pragma once
#include"../ViewPort/ViewportInfo.h"
#include"RObject/RMinimalObject.h"
#include"../Render/Render.h"
#include"../EngineMinimal.h"
#include"../Render/Pipeline/DX12Pipeline.h"
#include"../Core/public_singleton.h"
class RMeshComponent;
struct CreateObjectParam;
class RMeshManage:public PublicSingleton<RMeshManage>
{
public:
	RMeshManage();
	~RMeshManage();

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
};