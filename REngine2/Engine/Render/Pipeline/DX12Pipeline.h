#pragma once
#include"../../Interface/DXDeviceInterface.h"
#include"PipelineState/DXPipelineState.h"
#include"RootSignature/DXRootSignature.h"
#include"../../Mesh/Base/MeshType.h"
#include"../../Core/ViewPort/ViewportInfo.h"
#include"Geometry/GeometryMap.h"
class  DX12Pipeline:IDirectXDeviceInterface
{
public:
	 DX12Pipeline();
	~ DX12Pipeline();

	void Init();

	void ResetCommandList();

	void SetRootSignature();

	void BuildMesh(BMesh* mesh, const MeshRenderData& meshData);

	void BuildPipeline();

	void UpdateCalculations(const ViewportInfo viewportInfo);

	void Draw();
private:
	RShader m_VertexShader;
	RShader m_PixelShader;
	vector<D3D12_INPUT_ELEMENT_DESC> m_InputElementDesc;

	RGeometryMap m_GeometryMap;
	RDXRootSignature m_RootSignature;
	RDXPipelineState m_PipelineState;
};

