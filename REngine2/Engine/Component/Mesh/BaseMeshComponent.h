#include"StaticMeshComponent.h"

class BoxMeshComponent :public RStaticMeshComponent
{
public:
	BoxMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, float InDepth);

	void BuildKey(size_t& outKey, float height, float width, float depth);
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

	void BuildKey(size_t& outKey, float radius, float height, uint32_t axialSub, uint32_t heightSub);
};

class CustomMeshComponent :public RStaticMeshComponent
{
public:
	CustomMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, const char* name);

	void BuildKey(size_t& outKey, const char* name);
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

	void BuildKey(size_t& outKey, float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub);
};

class PlaneMeshComponent :public RStaticMeshComponent
{
public:
	PlaneMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InHeight, float InWidth, 
		uint32_t InHeightSubdivide, uint32_t InWidthSubdivide);

	void BuildKey(size_t& outKey, float height, float width, uint32_t heightSub, uint32_t widthSub);
};

class SphereMeshComponent :public RStaticMeshComponent
{
public:
	SphereMeshComponent();

	void CreateMesh(MeshRenderData& MeshData, float InRadius, 
		uint32_t InAxialSubdivision, uint32_t InHeightSubdivision);

	void BuildKey(size_t& outKey, float radius, uint32_t axialSub, uint32_t heightSub);
};