#pragma once
#include"Mesh.h"
#include"../../Core/ViewPort/ViewportInfo.h"
#include"../../Interface/DXDeviceInterface.h"
#include"../../Core/RObject/RMinimalObject.h"
#include"../../Render/Render.h"
#include"../../EngineMinimal.h"

class ResourcesUpdate;

class RMeshManage :public RMinimalObject, public IRenderingInterface,public IDirectXDeviceInterface
{
public:
	RMeshManage();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void UpdateCalculations(float DeltaTime, const ViewportInfo viewportInfo);

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

	D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView();
	D3D12_INDEX_BUFFER_VIEW GetIndexBufferView();
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
	ComPtr<ID3DBlob> CPUVertexBufferPtr;
	ComPtr<ID3DBlob> CPUIndexBufferPtr;

	ComPtr<ID3D12Resource> GPUVertexBufferPtr;
	ComPtr<ID3D12Resource> GPUIndexBufferPtr;

	ComPtr<ID3D12Resource> VertexBufferTmpPtr;
	ComPtr<ID3D12Resource> IndexBufferTmpPtr;

	ComPtr<ID3D12RootSignature>  RootSignature;
	ComPtr<ID3D12DescriptorHeap> CBVHeap;
	shared_ptr<ResourcesUpdate> ObjectConstants;
	shared_ptr<ResourcesUpdate> ViewportConstants;
	ComPtr<ID3D12PipelineState> PSO;

	RShader VertexShader;
	RShader PixelShader;

	vector<D3D12_INPUT_ELEMENT_DESC> InputElementDesc;
protected:
	UINT VertexSizeInBytes;
	UINT VertexStrideInBytes;

	UINT DescriptorOffset;

	UINT IndexSizeInBytes;
	DXGI_FORMAT IndexFormat;
	UINT IndexSize;

	XMFLOAT4X4 WorldMatrix;
};