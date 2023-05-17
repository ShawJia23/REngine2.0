#pragma once

#include"../Pipeline/DX12Pipeline.h"
#include"../../Config/RenderConfig.h"
#include"../../ViewPort/ViewportInfo.h"
#include "RenderEngine.h"
#include"../../Core/public_singleton.h"

class RActorManage;
class DX12Pipeline;
class DXRenderEngine :public RenderingEngine, public PublicSingleton<DXRenderEngine>
{
	friend class IRenderingInterface;
public:
	DXRenderEngine();
	~DXRenderEngine();

	virtual int PreInit(WinMainCommandParameters InParameters);

	virtual int Init(WinMainCommandParameters InParameters);
	virtual int PostInit();

	virtual void UpdateCalculations(GameTimer& gt, const ViewportInfo viewportInfo);
	virtual void Tick(GameTimer& gt);
	virtual void Tick() {};
	virtual void OnResetSize(int width, int height);

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();
	void StartSetMainViewportRenderTarget();
	void EndSetMainViewportRenderTarget();
	void ClearMainSwapChainCanvas();
protected:
	//初始化
	bool InitDirect3D();
	void CreateFactoryAndDevice();
	void CreateCommandQueue();
	void CreateSwapChain();
	void CreateDescriptor();
	void CreateCommandAllocator();
	void CreateFence();
	void InitSimpleLevel();
	void PostInitDirect3D();

protected:
	//每帧调用
	void WaitGPUCommandQueueComplete();
	void MoveToNextFrame();
	void BeforeDraw();
	void AfterDraw();
	void ChangeResources(int width, int height);

protected:
	UINT m_frameIndex;
	UINT64 m_fenceValues[2];
	HANDLE m_fenceEvent;
	bool m_tearingSupport;
	bool m_windowedMode;

	ComPtr<IDXGIFactory4> m_DXGIFactory;//创建 DirectX 图形基础结构 (DXGI) 对象
	ComPtr<ID3D12Device> m_D3dDevice;//创建命令分配器、命令列表、命令队列、Fence、资源、管道状态对象、堆、根签名、采样器和许多资源视图
	ComPtr<ID3D12Fence> m_fence;//一个用于同步 CPU 和一个或多个 GPU 的对象。

	ComPtr<ID3D12CommandQueue> m_commandQueue;//队列
	ComPtr<ID3D12CommandAllocator> m_commandAllocator; //存储
	ComPtr<ID3D12GraphicsCommandList> m_commandList;//命令列表

	ComPtr<IDXGISwapChain3> m_swapChain;

	//描述符对象和堆
	ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
	ComPtr<ID3D12DescriptorHeap> m_DSVHeap;

	vector<ComPtr<ID3D12Resource>> m_swapChainBuffer;
	ComPtr<ID3D12Resource> m_depthStencilBuffer;
protected:
	UINT M4XQualityLevels;
	bool bMSAA4XEnabled;
	DXGI_FORMAT BackBufferFormat;
	DXGI_FORMAT DepthStencilFormat;
	UINT RTVDescriptorSize;
	DX12Pipeline m_pipeline;
public:
	DX12Pipeline* GetDX12Pipeline() const { return const_cast<DX12Pipeline*>(&m_pipeline); }
	ID3D12Resource* GetCurrentSwapBuff() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentSwapBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentDepthStencilView() const;

	DXGI_FORMAT GetBackBufferFormat() const { return BackBufferFormat; }
	DXGI_FORMAT GetDepthStencilFormat() const { return DepthStencilFormat; }
	UINT GetDXGISampleCount()const;
	UINT GetDXGISampleQuality()const;
	ComPtr<ID3D12Fence> GetFence() { return m_fence; }
	ComPtr<ID3D12Device> GetD3dDevice() { return m_D3dDevice; }
	ComPtr<ID3D12GraphicsCommandList>GetCommandList() { return m_commandList; }
	ComPtr<ID3D12CommandAllocator>GetCommandAllocator() { return m_commandAllocator; }
	ComPtr<ID3D12CommandQueue> GetCommandQueue() { return m_commandQueue; }
	ComPtr<ID3D12DescriptorHeap> GetRTVHeap() { return  m_RTVHeap; }
	UINT64 GetCurrentFenceIndex() { return m_frameIndex; }
};