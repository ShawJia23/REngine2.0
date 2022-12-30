#pragma once
#include"../../../Interface/DXDeviceInterface.h"
#include"../DescriptorHeap/DXDescriptorHeap.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../../Mesh/MeshType.h"
#include"RenderMeshData.h"

class RMeshComponent;
class RMaterial;
class RenderLayerManage;
class RenderLayer;
struct RDXPipelineState;
struct ViewportInfo;

struct RGeometry :public IDirectXDeviceInterface_Struct
{
	friend struct RGeometryMap;

	bool RenderDataExistence(RMeshComponent* InKey, std::shared_ptr<RenderLayer> renderLayer);
	void BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData, std::shared_ptr<RenderLayer> renderLayer);

	void CreatePSO();

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();
protected:
	ComPtr<ID3DBlob> CPUVertexBufferPtr;
	ComPtr<ID3DBlob> CPUIndexBufferPtr;

	ComPtr<ID3D12Resource> GPUVertexBufferPtr;
	ComPtr<ID3D12Resource> GPUIndexBufferPtr;

	ComPtr<ID3D12Resource> VertexBufferTmpPtr;
	ComPtr<ID3D12Resource> IndexBufferTmpPtr;

	MeshRenderData m_MeshRenderData;
};


struct RGeometryMap :public IDirectXDeviceInterface_Struct
{
public:
	RGeometryMap();
	
	void Init();

	void Draw();
	void DrawTexture();

	void BuildConstantBufferView();

	void BuildMaterialsConstantBufferView();
	void BuildTextureConstantBuffer();
	void BuildDescriptorHeap();

	void BuildMesh(const MeshRenderData* renderingData);
	void BuildGeometry();

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

	void UpdateCalculations(const ViewportInfo viewportInfo);
	void UpdateMaterialShaderResourceView();

	ID3D12DescriptorHeap* GetHeap()const { return m_DescriptorHeap.GetHeap(); }

	void BuildMesh(RMeshComponent* mesh, const MeshRenderData& meshData);

	UINT GetMaterialsNumber();
	UINT GetMeshNumber();
	UINT GetLightsNumber();
	UINT GetTextureNumber();
	UINT GetDesptorSize();

	void SetPipelineState(RDXPipelineState* pipelineState);
	void BuildPSO();
private:
	map<int, RGeometry*> m_Geometrys;

	RDXDescriptorHeap m_DescriptorHeap;
	RConstantBufferView m_ObjectConstantBufferView;
	RConstantBufferView m_ViewportConstantBufferView;
	RConstantBufferView m_MaterialsBufferView;
	RConstantBufferView m_LightsBufferView;

	XMFLOAT4X4 m_WorldMatrix;

	UINT m_DescriptorOffset;

	UINT IndexSize;

	std::vector<RMaterial*> Materials;

	std::unique_ptr<RenderLayerManage> m_RenderLayerManage;
};