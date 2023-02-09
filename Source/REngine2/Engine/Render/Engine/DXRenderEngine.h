#pragma once
#include "RenderEngine.h"
#include"../../Config/RenderConfig.h"
#include"../../ViewPort/ViewportInfo.h"
class RMeshManage;
class RLightManage;
class RTextureManage;
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
	virtual void OnResetSize(int width, int height);

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

protected:
	//��ʼ��
	bool InitDirect3D();
	void CreateFactoryAndDevice();
	void CreateCommandQueue();
	void CreateSwapChain();
	void CreateDescriptor();
	void CreateCommandAllocator();
	void CreateFence();
	void InitSimpleLevel();
	void PostInitDirect3D();
	void CreateMesh();
	void LoadAsset();
protected:
	//ÿ֡����
	void WaitGPUCommandQueueComplete();
	void MoveToNextFrame();
	void BeforeDraw();
	void AfterDraw();
	void ChangeResources(int width, int height);

public:
	RWorld* m_World;

protected:
	RMeshManage* m_meshManage;
	RLightManage* m_lightManage;
	RTextureManage* m_textureManage;
protected:
	UINT m_frameIndex;
	UINT64 m_fenceValues[2];
	HANDLE m_fenceEvent;
	bool m_tearingSupport;
	bool m_windowedMode;

	ComPtr<IDXGIFactory4> m_DXGIFactory;//���� DirectX ͼ�λ����ṹ (DXGI) ����
	ComPtr<ID3D12Device> m_D3dDevice;//��������������������б�������С�Fence����Դ���ܵ�״̬���󡢶ѡ���ǩ�����������������Դ��ͼ
	ComPtr<ID3D12Fence> m_fence;//һ������ͬ�� CPU ��һ������ GPU �Ķ���

	ComPtr<ID3D12CommandQueue> m_commandQueue;//����
	ComPtr<ID3D12CommandAllocator> m_commandAllocator; //�洢
	ComPtr<ID3D12GraphicsCommandList> m_commandList;//�����б�

	ComPtr<IDXGISwapChain3> m_swapChain;

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
	UINT64 GetCurrentFenceIndex() { return m_frameIndex; }
	RMeshManage* GetMeshManage() { return m_meshManage; }
	RLightManage* GetLightManage() { return m_lightManage; }
	RTextureManage* GetTextureManage() { return m_textureManage; }
};