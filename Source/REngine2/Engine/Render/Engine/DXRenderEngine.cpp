#include "DXRenderEngine.h"
#include"../../Config/RenderConfig.h"
#include"../../Manage/MeshManage.h"
#include"../../Manage/ActorManage.h"
#include"../../World.h"
#include"../../Camera/Camera.h"

#if defined(_WIN32)

void DXRenderEngine::UpdateCalculations(GameTimer& gt, const ViewportInfo viewportInfo)
{
	m_pipeline.UpdateCalculations(viewportInfo);
}

void DXRenderEngine::BeforeDraw() 
{
	//指向哪个资源 转换其状态
	CD3DX12_RESOURCE_BARRIER ResourceBarrierPresent = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentSwapBuff(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_commandList->ResourceBarrier(1, &ResourceBarrierPresent);

	//需要每帧执行
	//绑定矩形框
	m_commandList->RSSetViewports(1, &RWorld::getInstance().GetCamera()->ViewprotInfo);
	m_commandList->RSSetScissorRects(1, &RWorld::getInstance().GetCamera()->ViewprotRect);

	//清除画布
	m_commandList->ClearRenderTargetView(GetCurrentSwapBufferView(),
		DirectX::Colors::Black,
		0, nullptr);

	//清除深度模板缓冲区
	m_commandList->ClearDepthStencilView(GetCurrentDepthStencilView(),
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.f, 0, 0, NULL);

	//输出的合并阶段
	D3D12_CPU_DESCRIPTOR_HANDLE SwapBufferView = GetCurrentSwapBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView = GetCurrentDepthStencilView();
	m_commandList->OMSetRenderTargets(1, &SwapBufferView,
		true, &DepthStencilView);
}

void DXRenderEngine::AfterDraw()
{
	CD3DX12_RESOURCE_BARRIER ResourceBarrierPresentRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentSwapBuff(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &ResourceBarrierPresentRenderTarget);

	//录入完成
	ANALYSIS_HRESULT(m_commandList->Close());

	//提交命令
	ID3D12CommandList* CommandList[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(CommandList), CommandList);
}

void DXRenderEngine::Tick(GameTimer& gt)
{
	//重置录制相关的内存，为下一帧做准备
	ANALYSIS_HRESULT(m_commandAllocator->Reset());

	m_pipeline.ResetCommandList();

	BeforeDraw();

	m_pipeline.Draw(gt);

	AfterDraw();

	UINT presentFlags = (m_tearingSupport && m_windowedMode) ? DXGI_PRESENT_ALLOW_TEARING : 0;
	//交换buff缓冲区
	ANALYSIS_HRESULT(m_swapChain->Present(0, presentFlags));
	MoveToNextFrame();

	m_pipeline.PostDraw(gt);
	//CPU等GPU
	WaitGPUCommandQueueComplete();
}

void DXRenderEngine::OnResetSize(int width, int height)
{
	if (m_D3dDevice)
	{
		//同步
		WaitGPUCommandQueueComplete();

		ANALYSIS_HRESULT(m_commandList->Reset(m_commandAllocator.Get(), NULL));

		for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
		{
			m_swapChainBuffer[i].Reset();
			m_fenceValues[i] = m_fenceValues[m_frameIndex];
		}

		DXGI_SWAP_CHAIN_DESC desc = {};
		m_swapChain->GetDesc(&desc);
		ANALYSIS_HRESULT(m_swapChain->ResizeBuffers
		(EngineRenderConfig::GetRenderConfig()->SwapChainCount, 
			width, 
			height, 
			BackBufferFormat, 
			DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));

		BOOL fullscreenState;
		ANALYSIS_HRESULT(m_swapChain->GetFullscreenState(&fullscreenState, nullptr));
		m_windowedMode = !fullscreenState;

		m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

		ChangeResources(width, height);

		//camera
		if (RWorld::getInstance().GetCamera())
			RWorld::getInstance().GetCamera()->OnResetSize(width, height);
		//mesh
		m_pipeline.OnResetSize(width, height);

		WaitGPUCommandQueueComplete();
	}
}

void DXRenderEngine::ChangeResources(int width, int height)
{
	m_depthStencilBuffer.Reset();
	//拿到描述size
	RTVDescriptorSize = m_D3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE HeapHandle(m_RTVHeap->GetCPUDescriptorHandleForHeapStart());
	for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
	{
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_swapChainBuffer[i]));
		m_D3dDevice->CreateRenderTargetView(m_swapChainBuffer[i].Get(), nullptr, HeapHandle);
		HeapHandle.Offset(1, RTVDescriptorSize);
	}

	D3D12_RESOURCE_DESC ResourceDesc;
	ResourceDesc.Width = width;
	ResourceDesc.Height = height;
	ResourceDesc.Alignment = 0;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	ResourceDesc.SampleDesc.Count = bMSAA4XEnabled ? 4 : 1;
	ResourceDesc.SampleDesc.Quality = bMSAA4XEnabled ? (M4XQualityLevels - 1) : 0;
	ResourceDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	ResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	D3D12_CLEAR_VALUE ClearValue;
	ClearValue.DepthStencil.Depth = 1.f;
	ClearValue.DepthStencil.Stencil = 0;
	ClearValue.Format = DepthStencilFormat;

	CD3DX12_HEAP_PROPERTIES Properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	m_D3dDevice->CreateCommittedResource(
		&Properties,
		D3D12_HEAP_FLAG_NONE, &ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON, &ClearValue,
		IID_PPV_ARGS(m_depthStencilBuffer.GetAddressOf()));

	D3D12_DEPTH_STENCIL_VIEW_DESC DSVDesc;
	DSVDesc.Format = DepthStencilFormat;
	DSVDesc.Texture2D.MipSlice = 0;
	DSVDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	DSVDesc.Flags = D3D12_DSV_FLAG_NONE;
	m_D3dDevice->CreateDepthStencilView(m_depthStencilBuffer.Get(), &DSVDesc, m_DSVHeap->GetCPUDescriptorHandleForHeapStart());

	CD3DX12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_depthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE);

	m_commandList->ResourceBarrier(1, &Barrier);

	m_commandList->Close();

	ID3D12CommandList* CommandList[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(CommandList), CommandList);

	if (RWorld::getInstance().GetCamera())
	{
		RWorld::getInstance().GetCamera()->OnResetSize(width, height);
	}
}

void DXRenderEngine::WaitGPUCommandQueueComplete()
{
	//向GUP设置新的隔离点 等待GPU处理玩信号
	ANALYSIS_HRESULT(m_commandQueue->Signal(m_fence.Get(), m_fenceValues[m_frameIndex]));

	//GPU完成后会通知我们的Handle
	ANALYSIS_HRESULT(m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_fenceEvent));

	//等待GPU,阻塞主线程
	WaitForSingleObject(m_fenceEvent, INFINITE);

	m_fenceValues[m_frameIndex]++;
}

void DXRenderEngine::MoveToNextFrame()
{
	// Schedule a Signal command in the queue.
	const UINT64 currentFenceValue = m_fenceValues[m_frameIndex];
	ANALYSIS_HRESULT(m_commandQueue->Signal(m_fence.Get(), currentFenceValue));

	// Update the frame index.
	//m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
	// If the next frame is not ready to be rendered yet, wait until it is ready.
	if (m_fence->GetCompletedValue() < m_fenceValues[m_frameIndex])
	{
		ANALYSIS_HRESULT(m_fence->SetEventOnCompletion(m_fenceValues[m_frameIndex], m_fenceEvent));
		WaitForSingleObjectEx(m_fenceEvent, INFINITE, FALSE);
	}

	// Set the fence value for the next frame.
	m_fenceValues[m_frameIndex] = currentFenceValue + 1;
}

DXRenderEngine::DXRenderEngine()
	:m_frameIndex(0)
	, M4XQualityLevels(0)
	, bMSAA4XEnabled(false)
	, BackBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM)
	, DepthStencilFormat(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT)
{
	for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
	{
		m_swapChainBuffer.push_back(ComPtr<ID3D12Resource>());
	}

}

int DXRenderEngine::PreInit(WinMainCommandParameters InParameters)
{
	Engine_Log("PreInit DXRenderEngine");
	return 0;
}

int DXRenderEngine::Init(WinMainCommandParameters InParameters)
{
	InitDirect3D();

	PostInitDirect3D();

	m_pipeline.Init();

	Engine_Log("Init DXRenderEngine");

	return 0;
}

int DXRenderEngine::PostInit()
{
	Engine_Log("PostInit DXRenderEngine");

	ANALYSIS_HRESULT(m_commandList->Reset(m_commandAllocator.Get(), NULL));
	{
		RActorManage::getInstance().LoadObject();
		RActorManage::getInstance().LoadAsset();
	}
	Engine_Log("W A S D to Move");
	Engine_Log("Press RMouse + Move Mouse to Rotate");
	
	m_pipeline.BuildPipeline();

	ANALYSIS_HRESULT(m_commandList->Close());

	ID3D12CommandList* CommandList[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(CommandList), CommandList);

	WaitGPUCommandQueueComplete();

	return 0;
}

bool DXRenderEngine::InitDirect3D()
{
	CreateFactoryAndDevice();
	CreateCommandQueue();
	CreateSwapChain();
	CreateDescriptor();
	CreateFence();
	CreateCommandAllocator();
	InitSimpleLevel();

	return false;
}

void DXRenderEngine::CreateFactoryAndDevice()
{
	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
	ComPtr<ID3D12Debug> D3D12Debug;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&D3D12Debug))))
	{
		D3D12Debug->EnableDebugLayer();

		dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
	}
#endif

	ANALYSIS_HRESULT(CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_DXGIFactory)));

	HRESULT D3dDeviceResult = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_D3dDevice));
	if (FAILED(D3dDeviceResult))
	{
		ComPtr<IDXGIAdapter> WARPAdapter;
		ANALYSIS_HRESULT(m_DXGIFactory->EnumWarpAdapter(IID_PPV_ARGS(&WARPAdapter)));
		ANALYSIS_HRESULT(D3D12CreateDevice(WARPAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_D3dDevice)));
	}
}

void DXRenderEngine::CreateCommandQueue()
{
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;//直接
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_commandQueue)));
}

void DXRenderEngine::CreateSwapChain()
{
	//m_tearingSupport = true;
	//交换链
	DXGI_SWAP_CHAIN_DESC1 SwapChainDesc;
	SwapChainDesc.Width = EngineRenderConfig::GetRenderConfig()->ScreenWidth;
	SwapChainDesc.Height = EngineRenderConfig::GetRenderConfig()->ScreenHeight;
	SwapChainDesc.BufferCount = EngineRenderConfig::GetRenderConfig()->SwapChainCount;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//使用表面或资源作为输出渲染目标。
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = m_tearingSupport ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;
	SwapChainDesc.Format = BackBufferFormat;//纹理格式
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Stereo = 0;
	SwapChainDesc.Scaling = DXGI_SCALING_NONE;
	SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	//多重采样设置
	SwapChainDesc.SampleDesc.Count = GetDXGISampleCount();
	SwapChainDesc.SampleDesc.Quality = GetDXGISampleQuality();

	ComPtr<IDXGISwapChain1> swapChain;
	HRESULT reset = m_DXGIFactory->CreateSwapChainForHwnd(
		m_commandQueue.Get(),        // Swap chain needs the queue so that it can force a flush on it.
		MianWindowsHandle,
		&SwapChainDesc,
		nullptr,
		nullptr,
		&swapChain
	);

	if (m_tearingSupport)
	{
		// When tearing support is enabled we will handle ALT+Enter key presses in the
		// window message loop rather than let DXGI handle it by calling SetFullscreenState.
		m_DXGIFactory->MakeWindowAssociation(MianWindowsHandle, DXGI_MWA_NO_ALT_ENTER);
	}

	ANALYSIS_HRESULT(swapChain.As(&m_swapChain));
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}
 
void DXRenderEngine::CreateDescriptor()
{
	//资源描述符
	////////////////////////////////////////////////////////////////////
	//D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV	//CBV常量缓冲区视图 SRV着色器资源视图 UAV无序访问视图
	//D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER		//采样器视图
	//D3D12_DESCRIPTOR_HEAP_TYPE_RTV			//渲染目标的视图资源
	//D3D12_DESCRIPTOR_HEAP_TYPE_DSV			//深度/模板的视图资源
	//RTV
	D3D12_DESCRIPTOR_HEAP_DESC RTVDescriptorHeapDesc;
	RTVDescriptorHeapDesc.NumDescriptors = EngineRenderConfig::GetRenderConfig()->SwapChainCount + 1;
	RTVDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	RTVDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	RTVDescriptorHeapDesc.NodeMask = 0;
	ANALYSIS_HRESULT(m_D3dDevice->CreateDescriptorHeap(
		&RTVDescriptorHeapDesc,
		IID_PPV_ARGS(m_RTVHeap.GetAddressOf())));

	//DSV
	D3D12_DESCRIPTOR_HEAP_DESC DSVDescriptorHeapDesc;
	DSVDescriptorHeapDesc.NumDescriptors = 1;
	DSVDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	DSVDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	DSVDescriptorHeapDesc.NodeMask = 0;
	ANALYSIS_HRESULT(m_D3dDevice->CreateDescriptorHeap(
		&DSVDescriptorHeapDesc,
		IID_PPV_ARGS(m_DSVHeap.GetAddressOf())));
}

void DXRenderEngine::CreateCommandAllocator()
{
	//	ID3D12CommandAllocator Allocator();
	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(m_commandAllocator.GetAddressOf())));

	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandList(
		0, //默认单个Gpu 
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,//直接类型
		m_commandAllocator.Get(),//将Commandlist关联到Allocator
		NULL,//ID3D12PipelineState
		IID_PPV_ARGS(m_commandList.GetAddressOf())));

	ANALYSIS_HRESULT(m_commandList->Close());
}

void DXRenderEngine::CreateFence()
{
	ANALYSIS_HRESULT(m_D3dDevice->CreateFence(m_fenceValues[m_frameIndex], D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));
	m_fenceValues[m_frameIndex]++;

	m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (m_fenceEvent == nullptr)
	{
		ANALYSIS_HRESULT(HRESULT_FROM_WIN32(GetLastError()));
	}
}

void DXRenderEngine::InitSimpleLevel()
{
	//多重采样
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS QualityLevels;
	QualityLevels.Format = BackBufferFormat;
	QualityLevels.SampleCount = 4;
	QualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS::D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	QualityLevels.NumQualityLevels = 0;

	ANALYSIS_HRESULT(m_D3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&QualityLevels,
		sizeof(QualityLevels)));

	M4XQualityLevels = QualityLevels.NumQualityLevels;
}

void DXRenderEngine::PostInitDirect3D()
{
	OnResetSize(EngineRenderConfig::GetRenderConfig()->ScreenWidth,
		EngineRenderConfig::GetRenderConfig()->ScreenHeight);
}

DXRenderEngine::~DXRenderEngine()
{
	CloseHandle(m_fenceEvent);
	m_swapChain.Reset();
}

int DXRenderEngine::PreExit()
{
	Engine_Log("PreExit DXRenderEngine.");
	return 0;
}

int DXRenderEngine::Exit()
{
	Engine_Log("Exit DXRenderEngine.");
	return 0;
}

int DXRenderEngine::PostExit()
{
	EngineRenderConfig::Destroy();

	Engine_Log("PostExit DXRenderEngine.");
	return 0;
}

ID3D12Resource* DXRenderEngine::GetCurrentSwapBuff() const
{
	return m_swapChainBuffer[m_frameIndex].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE DXRenderEngine::GetCurrentSwapBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		m_RTVHeap->GetCPUDescriptorHandleForHeapStart(),
		m_frameIndex, RTVDescriptorSize);
}

D3D12_CPU_DESCRIPTOR_HANDLE DXRenderEngine::GetCurrentDepthStencilView() const
{
	return m_DSVHeap->GetCPUDescriptorHandleForHeapStart();
}

UINT DXRenderEngine::GetDXGISampleCount() const
{
	return bMSAA4XEnabled ? 4 : 1;;
}

UINT DXRenderEngine::GetDXGISampleQuality() const
{
	return bMSAA4XEnabled ? (M4XQualityLevels - 1) : 0;
}

#endif