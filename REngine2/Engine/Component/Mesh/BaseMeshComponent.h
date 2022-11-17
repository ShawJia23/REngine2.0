#include"StaticMeshComponent.h"

class BoxMeshComponent :public RStaticMeshComponent
{
public:
	BoxMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, float InDepth);
};

class ConeMeshComponent :public RStaticMeshComponent
{
public:
	ConeMeshComponent();

	void CreateMesh(
		MeshRenderData& MeshData,
		float InRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);
};

class CustomMeshComponent :public RStaticMeshComponent
{
public:
	CustomMeshComponent();

	void CreateMesh(MeshRenderData& MeshData,int i);
};

class CylinderMeshComponent :public RStaticMeshComponent
{
public:
	CylinderMeshComponent();

	void CreateMesh(
		MeshRenderData& MeshData,
		float InTopRadius,
		float InBottomRadius,
		float InHeight,
		uint32_t InAxialSubdivision,
		uint32_t InHeightSubdivision);
};

class PlaneMeshComponent :public RStaticMeshComponent
{
public:
	PlaneMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, 
		uint32_t InHeightSubdivide, uint32_t InWidthSubdivide);
};

class SphereMeshComponent :public RStaticMeshComponent
{
public:
	SphereMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InRadius, 
		uint32_t InAxialSubdivision, uint32_t InHeightSubdivision);
};