#pragma once
#include "RenderEngine.h"
#include"../../Core/ViewPort/ViewportInfo.h"
class RMeshManage;
class RWorld;
class DXRenderEngine :public RenderingEngine
{
	friend class IRenderingInterface;
public:
	DXRenderEngine();
	~DXRenderEngine();

	virtual int PreInit(WinMainCommandParameters InParameters);

	virtual int Init(WinMainCommandParameters InParameters);
	virtual int PostInit();

	virtual void UpdateCalculations(float DeltaTime, const ViewportInfo viewportInfo);
	virtual void Tick(float DeltaTime);

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();
public:
	ID3D12Resource* GetCurrentSwapBuff() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentSwapBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentDepthStencilView() const;

	DXGI_FORMAT GetBackBufferFormat() const { return BackBufferFormat; }
	DXGI_FORMAT GetDepthStencilFormat() const { return DepthStencilFormat; }
	UINT GetDXGISampleCount()const;
	UINT GetDXGISampleQuality()const;

	ComPtr<ID3D12Fence> GetFence() { return m_fence; }
	ComPtr<ID3D12Device> GetD3dDevice() { return m_D3dDevice; }

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return m_commandList; }
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() { return m_commandAllocator; }
	ComPtr<ID3D12CommandQueue> GetCommandQueue() { return m_commandQueue; }

	UINT64 GetCurrentFenceIndex() { return m_currentFenceIndex; }

	RMeshManage* GetMeshManage() { return m_meshManage; }

protected:
	void WaitGPUCommandQueueComplete();

	bool InitDirect3D();
	void PostInitDirect3D();

public:
	RWorld* m_World;

protected:
	RMeshManage* m_meshManage;

protected:
	UINT64 m_currentFenceIndex;
	int m_currentSwapBuffIndex;

	ComPtr<IDXGIFactory4> m_DXGIFactory;//���� DirectX ͼ�λ����ṹ (DXGI) ����
	ComPtr<ID3D12Device> m_D3dDevice;//��������������������б�������С�Fence����Դ���ܵ�״̬���󡢶ѡ���ǩ�����������������Դ��ͼ
	ComPtr<ID3D12Fence> m_fence;//һ������ͬ�� CPU ��һ������ GPU �Ķ���

	ComPtr<ID3D12CommandQueue> m_commandQueue;//����
	ComPtr<ID3D12CommandAllocator> m_commandAllocator; //�洢
	ComPtr<ID3D12GraphicsCommandList> m_commandList;//�����б�

	ComPtr<IDXGISwapChain> m_swapChain;

	//����������Ͷ�
	ComPtr<ID3D12DescriptorHeap> m_RTVHeap;
	ComPtr<ID3D12DescriptorHeap> m_DSVHeap;

	vector<ComPtr<ID3D12Resource>> m_swapChainBuffer;
	ComPtr<ID3D12Resource> m_depthStencilBuffer;

	//����Ļ���ӿ��й�
	D3D12_VIEWPORT m_viewprotInfo;
	D3D12_RECT m_viewprotRect;
protected:
	UINT M4XQualityLevels;
	bool bMSAA4XEnabled;
	DXGI_FORMAT BackBufferFormat;
	DXGI_FORMAT DepthStencilFormat;
	UINT RTVDescriptorSize;
};