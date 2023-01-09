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
	RGeometry();

	friend struct RGeometryMap;

	void BuildMesh(const size_t meshHash, RMeshComponent* mesh, const MeshRenderData& meshData, std::shared_ptr<RenderLayer> renderLayer);
	void DuplicateMesh(RMeshComponent* mesh, std::shared_ptr<RRenderData>& meshData, int key, std::unique_ptr<RenderLayerManage>& renderLayerManage);
	bool FindMeshRenderingDataByHash(const size_t& inHash, std::shared_ptr<RRenderData>& meshData,int renderLayerIndex = -1);

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

protected:
	//唯一性的渲染池
	static map<size_t, std::shared_ptr<RRenderData>> UniqueRenderingDatas;

public:
	//真正的渲染池 里面会有重复的 key (size_t)
	static vector<std::shared_ptr<RRenderData>> RenderingDatas;
};


struct RGeometryMap :public IDirectXDeviceInterface_Struct
{
public:
	RGeometryMap();
	
	void Init();

	void Draw();
	void PostDraw(float DeltaTime);
	void DrawTexture();

	void BuildConstantBufferView();

	void BuildMaterialsConstantBufferView();
	void BuildTextureConstantBuffer();
	void BuildDescriptorHeap();

	void BuildMesh(const MeshRenderData* renderingData);
	void DuplicateMesh(RMeshComponent* mesh, std::shared_ptr<RRenderData>& meshData);
	bool FindMeshRenderingDataByHash(const size_t& inHash, std::shared_ptr<RRenderData>& meshData,int renderLayerIndex = -1);
	
	void BuildGeometry();

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

	void UpdateCalculations(const ViewportInfo viewportInfo);
	void UpdateMaterialShaderResourceView();

	ID3D12DescriptorHeap* GetHeap()const { return m_DescriptorHeap.GetHeap(); }

	void BuildMesh(const size_t meshHash, RMeshComponent* mesh, const MeshRenderData& meshData);

	UINT GetMaterialsNumber();
	UINT GetMeshNumber();
	UINT GetLightsNumber();
	UINT GetTextureNumber();
	UINT GetCubeMapNumber();
	UINT GetDesptorSize();

	void InitRenderLayer(RDXPipelineState* pipelineState);
	void BuildPSO();

	RConstantBufferView GetObjectConstantBufferView() { return m_ObjectConstantBufferView; }
	RGeometry GetRGeometry(int ID) 
	{
		if(m_Geometrys.find(ID)!= m_Geometrys.end())
			return m_Geometrys[ID];
		return RGeometry();
	}
protected:
	map<int, RGeometry> m_Geometrys;
private:
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