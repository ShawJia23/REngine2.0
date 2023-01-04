#pragma once
#include"../../Interface/DXDeviceInterface.h"
#include"RootSignature/DXRootSignature.h"
#include"../../Mesh/MeshType.h"
#include"../../Core/ViewPort/ViewportInfo.h"
#include"Geometry/GeometryMap.h"
#include"RenderLayer/RenderLayerManage.h"
#include"UI/ImGuiPipeline.h"

class RMeshComponent;
class  DX12Pipeline:IDirectXDeviceInterface
{
public:
	 DX12Pipeline();
	~ DX12Pipeline();

	void Init();

	void ResetCommandList();

	void SetRootSignature();

	void BuildMesh(const size_t meshHash,RMeshComponent* mesh, const MeshRenderData& meshData);

	void BuildPipeline();

	void UpdateCalculations(const ViewportInfo viewportInfo);

	void Draw(float DeltaTime);

	void BuildPSO();

public:
	bool FindMeshRenderingDataByHash(const size_t& inHash, std::shared_ptr<RRenderData>& meshData,int renderLayerIndex);
private:
	RGeometryMap m_GeometryMap;
	RDXPipelineState m_PipelineState;
	RDXRootSignature m_RootSignature;
	RImGuiPipeline m_UIPipeline;
};

