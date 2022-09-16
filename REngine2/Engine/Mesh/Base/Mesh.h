#pragma once
#include "../../Render/Render.h"
#include "MeshType.h"
#include "../../Shader/Shader.h"

struct ObjectTransformation
{
	ObjectTransformation();

	XMFLOAT4X4 World;

	static XMFLOAT4X4 IdentityMatrix4x4();
};

class BMesh : public IRenderingInterface
{
public:
	BMesh();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

	static BMesh* CreateMesh(const MeshRenderingData* InRenderingData);

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();

protected:
	ComPtr<ID3DBlob>m_CPUVertexBufferPtr;
	ComPtr<ID3DBlob> m_CPUIndexBufferPtr;

	ComPtr<ID3D12Resource> m_GPUVertexBufferPtr;
	ComPtr<ID3D12Resource> m_GPUIndexBufferPtr;

	ComPtr<ID3D12Resource> m_vertexBufferTmpPtr;
	ComPtr<ID3D12Resource> m_indexBufferTmpPtr;

	ComPtr<ID3D12RootSignature>  m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_CBVHeap;
	shared_ptr<RenderingResourcesUpdate> m_objectConstants;

	ComPtr<ID3D12PipelineState> m_PSO;

	RShader m_vertexShader;
	RShader m_pixelShader;

	vector<D3D12_INPUT_ELEMENT_DESC> m_inputElementDesc;
protected:
	UINT m_vertexSizeInBytes;
	UINT m_vertexStrideInBytes;

	UINT m_indexSizeInBytes;
	DXGI_FORMAT m_indexFormat;
	UINT m_indexSize;

	XMFLOAT4X4 m_worldMatrix;
	XMFLOAT4X4 m_viewMatrix;
	XMFLOAT4X4 m_projectMatrix;
};