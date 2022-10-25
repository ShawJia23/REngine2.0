#pragma once
#include"../../../Interface/DXDeviceInterface.h"
#include"../DescriptorHeap/DXDescriptorHeap.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../../Core/ViewPort/ViewportInfo.h"
#include"../../../Mesh/Base/MeshType.h"
#include"RenderMeshData.h"
struct RGeometry :public IDirectXDeviceInterface_Struct
{
	friend struct RGeometryMap;

	bool RenderDataExistence(BMesh* InKey);
	void BuildMesh(BMesh* InMesh, const MeshRenderData& MeshData);

	void Build();

	UINT GetDrawObjectNumber() const { return m_RenderDatas.size(); }

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

	vector<RRenderData> m_RenderDatas;
};


struct RGeometryMap :public IDirectXDeviceInterface_Struct
{
public:
	RGeometryMap();
	
	void Init();

	void Draw();
	void DrawLights();
	void DrawViewport();
	void DrawMesh();

	void BuildConstantBufferView();
	void BuildMeshConstantBufferView();
	void BuildViewportConstantBufferView();
	void BuildMaterialsConstantBufferView();
	void BuildLightsConstantBufferView();
	void BuildDescriptorHeap();

	void BuildMesh(const MeshRenderData* renderingData);
	void BuildGeometry();

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

	void UpdateCalculations(const ViewportInfo viewportInfo);

	ID3D12DescriptorHeap* GetHeap()const { return m_DescriptorHeap.GetHeap(); }

	void BuildMesh(BMesh* mesh, const MeshRenderData& meshData);

	UINT GetMaterialsNumber();
	UINT GetMeshNumber();
	UINT GetLightsNumber();
private:
	map<int, RGeometry> m_Geometrys;

	RDXDescriptorHeap m_DescriptorHeap;
	RConstantBufferView m_ObjectConstantBufferView;
	RConstantBufferView m_ViewportConstantBufferView;
	RConstantBufferView m_MaterialsBufferView;
	RConstantBufferView m_LightsBufferView;

	XMFLOAT4X4 m_WorldMatrix;

	UINT m_DescriptorOffset;

	UINT IndexSize;
};