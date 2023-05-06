#pragma once
#include"../../../EngineMinimal.h"
class RRenderTarget :std::enable_shared_from_this<RRenderTarget>
{
public:
	RRenderTarget();
	~RRenderTarget();
public:
	virtual void Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat);
	virtual void ResetRenderTarget(UINT inWidth, UINT inHeight);

	virtual void BuildRenderTargetMap() {}
	virtual void BuildSRVDescriptors() {}
	virtual void BuildRTVDescriptors() {}

	void ResetViewport(UINT InWidth, UINT InHeight);
	void ResetScissorRect(UINT InWidth, UINT InHeight);

public:
	FORCEINLINE ID3D12Resource* GetRenderTarget() const { return RenderTargetMap.Get(); }
	FORCEINLINE D3D12_VIEWPORT GetViewport() const { return Viewport; }
	FORCEINLINE D3D12_RECT GetScissorRect()const { return ScissorRect; }

	CD3DX12_GPU_DESCRIPTOR_HANDLE& GetGPUSRVOffset() { return GPUShaderResourceView; }
	CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCPUSRVOffset() { return CPUShaderResourceView; }

	CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCPURenderTargetView() { return RenderTargetViewCPU; }

protected:
	UINT Width;
	UINT Height;
	DXGI_FORMAT Format;

	D3D12_VIEWPORT Viewport;
	D3D12_RECT ScissorRect;

	//放数据的地方
	ComPtr<ID3D12Resource> RenderTargetMap;

	//SRV
	CD3DX12_CPU_DESCRIPTOR_HANDLE CPUShaderResourceView;
	CD3DX12_GPU_DESCRIPTOR_HANDLE GPUShaderResourceView;

	//RTV
	CD3DX12_CPU_DESCRIPTOR_HANDLE RenderTargetViewCPU;
};