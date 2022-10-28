#include "DXRenderEngine.h"

#include"../../Config/RenderConfig.h"
#include"../../Mesh/Base/MeshManage.h"
#include"../../Mesh/Materials/Material.h"
#include"../../Core/World.h"
#include".././../Mesh/BaseMesh.h"
#if defined(_WIN32)


DXRenderEngine::DXRenderEngine()
	:m_currentFenceIndex(0)
	, M4XQualityLevels(0)
	, bMSAA4XEnabled(false)
	, BackBufferFormat(DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM)
	, DepthStencilFormat(DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT)
	, m_currentSwapBuffIndex(0)
{
	for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
	{
		m_swapChainBuffer.push_back(ComPtr<ID3D12Resource>());
	}

	bTick = false;

	m_meshManage = new RMeshManage();
}

DXRenderEngine::~DXRenderEngine()
{
	delete m_meshManage;
}

int DXRenderEngine::PreInit(WinMainCommandParameters InParameters)
{
	Engine_Log("DX��Ⱦ Ԥ�ȳ�ʼ�� ���");
	return 0;
}

int DXRenderEngine::Init(WinMainCommandParameters InParameters)
{
	InitDirect3D();

	PostInitDirect3D();

	m_meshManage->Init();

	Engine_Log("DX��Ⱦ ��ʼ�� ���");

	return 0;
}

int DXRenderEngine::PostInit()
{
	Engine_Log("DX��Ⱦ �Ϻ��ʼ�� ���");

	ANALYSIS_HRESULT(m_commandList->Reset(m_commandAllocator.Get(), NULL));
	{
		//����Mesh
		PlaneMesh* pMesh = m_World->CreateActorObject<PlaneMesh>();
		if(pMesh)
		{
			pMesh->CreateMesh(4.f, 3.f, 20, 20);
			pMesh->SetPosition(XMFLOAT3(0.f, -2.f, 0.f));
			pMesh->SetScale(fvector_3d(10.f, 10.f, 10.f));
		}

		SphereMesh* pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(8.f, 2, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::BlinnPhong);

				pMaterial->SetRoughness(0.8f);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(0.f, 6, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::WrapLight);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(-4.f, 6, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::Minnaert);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(8.f, 6, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::Banded);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(8.f, 10, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::GradualBanded);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(4.f, 10, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::FinalBanded);
				pMaterial->SetRoughness(0.8f);
			}
		}
		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(0.f, 10, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(0.2f, 0.8f, 0.3f, 1.f));
				pMaterial->SetMaterialType(EMaterialType::Back);
			}
		}

		pSMesh = m_World->CreateActorObject<SphereMesh>();
		if (pSMesh)
		{
			pSMesh->CreateMesh(2.f, 50, 50);
			pSMesh->SetPosition(XMFLOAT3(-4.f, 10, 0.f));
			if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
			{
				pMaterial->SetBaseColor(fvector_4d(1.f));
				pMaterial->SetMaterialType(EMaterialType::Normal);
			}
		}
	}
	m_meshManage->BuildPipeline();

	ANALYSIS_HRESULT(m_commandList->Close());

	ID3D12CommandList* CommandList[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(CommandList), CommandList);

	WaitGPUCommandQueueComplete();

	return 0;
}

void DXRenderEngine::UpdateCalculations(float DeltaTime, const ViewportInfo viewportInfo)
{
	m_meshManage->UpdateCalculations(DeltaTime,viewportInfo);
}

void DXRenderEngine::Tick(float DeltaTime)
{
	//����¼����ص��ڴ棬Ϊ��һ֡��׼��
	ANALYSIS_HRESULT(m_commandAllocator->Reset());

	m_meshManage->PreDraw(DeltaTime);

	//ָ���ĸ���Դ ת����״̬
	CD3DX12_RESOURCE_BARRIER ResourceBarrierPresent = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentSwapBuff(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_commandList->ResourceBarrier(1, &ResourceBarrierPresent);

	//��Ҫÿִ֡��
	//�󶨾��ο�
	m_commandList->RSSetViewports(1, &m_viewprotInfo);
	m_commandList->RSSetScissorRects(1, &m_viewprotRect);

	//�������
	m_commandList->ClearRenderTargetView(GetCurrentSwapBufferView(),
		DirectX::Colors::Black,
		0, nullptr);

	//������ģ�建����
	m_commandList->ClearDepthStencilView(GetCurrentDepthStencilView(),
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
		1.f, 0, 0, NULL);

	//����ĺϲ��׶�
	D3D12_CPU_DESCRIPTOR_HANDLE SwapBufferView = GetCurrentSwapBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView = GetCurrentDepthStencilView();
	m_commandList->OMSetRenderTargets(1, &SwapBufferView,
		true, &DepthStencilView);

	m_meshManage->Draw(DeltaTime);
	m_meshManage->PostDraw(DeltaTime);

	CD3DX12_RESOURCE_BARRIER ResourceBarrierPresentRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentSwapBuff(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	m_commandList->ResourceBarrier(1, &ResourceBarrierPresentRenderTarget);

	//¼�����
	ANALYSIS_HRESULT(m_commandList->Close());

	//�ύ����
	ID3D12CommandList* CommandList[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(CommandList), CommandList);

	//��������buff������
	ANALYSIS_HRESULT(m_swapChain->Present(0, 0));
	m_currentSwapBuffIndex = !(bool)m_currentSwapBuffIndex;

	//CPU��GPU
	WaitGPUCommandQueueComplete();
}

int DXRenderEngine::PreExit()
{


	Engine_Log("DX��Ⱦ Ԥ���˳� ���.");
	return 0;
}

int DXRenderEngine::Exit()
{

	Engine_Log("DX��Ⱦ �˳� ���.");
	return 0;
}

int DXRenderEngine::PostExit()
{
	EngineRenderConfig::Destroy();

	Engine_Log("DX��Ⱦ �Ϻ��˳� ���.");
	return 0;
}

ID3D12Resource* DXRenderEngine::GetCurrentSwapBuff() const
{
	return m_swapChainBuffer[m_currentSwapBuffIndex].Get();
}

D3D12_CPU_DESCRIPTOR_HANDLE DXRenderEngine::GetCurrentSwapBufferView() const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		m_RTVHeap->GetCPUDescriptorHandleForHeapStart(),
		m_currentSwapBuffIndex, RTVDescriptorSize);
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

void DXRenderEngine::WaitGPUCommandQueueComplete()
{
	m_currentFenceIndex++;

	//��GUP�����µĸ���� �ȴ�GPU�������ź�
	ANALYSIS_HRESULT(m_commandQueue->Signal(m_fence.Get(), m_currentFenceIndex));

	if (m_fence->GetCompletedValue() < m_currentFenceIndex)
	{
		//�������һ���¼��ں˶���,�����ظ��ں˶���ľ��.
		//SECURITY_ATTRIBUTES
		//CREATE_EVENT_INITIAL_SET  0x00000002
		//CREATE_EVENT_MANUAL_RESET 0x00000001
		//ResetEvents
		HANDLE EventEX = CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS);

		//GPU��ɺ��֪ͨ���ǵ�Handle
		ANALYSIS_HRESULT(m_fence->SetEventOnCompletion(m_currentFenceIndex, EventEX));

		//�ȴ�GPU,�������߳�
		WaitForSingleObject(EventEX, INFINITE);
		CloseHandle(EventEX);
	}
}

bool DXRenderEngine::InitDirect3D()
{
	//Debug
	ComPtr<ID3D12Debug> D3D12Debug;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&D3D12Debug))))
	{
		D3D12Debug->EnableDebugLayer();
	}

	////////////////////////////////////////////////////////////////////////////////////////
		//HRESULT
		//S_OK				0x00000000
		//E_UNEXPECTED		0x8000FFFF �����ʧ��
		//E_NOTIMPL			0x80004001 δʵ��
		//E_OUTOFMEMORY		0x8007000E δ�ܷ���������ڴ�
		//E_INVALIDARG		0x80070057 һ������������Ч 
		//E_NOINTERFACE		0x80004002 ��֧�ִ˽ӿ�
		//E_POINTER			0x80004003 ��Чָ��
		//E_HANDLE			0x80070006 ��Ч���
		//E_ABORT			0x80004004 ������ֹ
		//E_FAIL			0x80004005 ����
		//E_ACCESSDENIED	0x80070005 һ��ķ��ʱ��ܾ�����
	ANALYSIS_HRESULT(CreateDXGIFactory1(IID_PPV_ARGS(&m_DXGIFactory)));

	/*
	D3D_FEATURE_LEVEL_9_1  Ŀ�깦�ܼ���֧��Direct3D 9.1���� shader model 2.
	D3D_FEATURE_LEVEL_9_2  Ŀ�깦�ܼ���֧��Direct3D 9.2���� shader model 2.
	D3D_FEATURE_LEVEL_9_3  Ŀ�깦�ܼ���֧��Direct3D 9.3���� shader model 3.
	D3D_FEATURE_LEVEL_10_0 Ŀ�깦�ܼ���֧��Direct3D 10.0���� shader model 4.
	D3D_FEATURE_LEVEL_10_1 Ŀ�깦�ܼ���֧��Direct3D 10.1���� shader model 4.
	D3D_FEATURE_LEVEL_11_0 Ŀ�깦�ܼ���֧��Direct3D 11.0���� shader model 5.
	*/

	HRESULT D3dDeviceResult = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_D3dDevice));
	if (FAILED(D3dDeviceResult))
	{
		//warp
		ComPtr<IDXGIAdapter> WARPAdapter;
		ANALYSIS_HRESULT(m_DXGIFactory->EnumWarpAdapter(IID_PPV_ARGS(&WARPAdapter)));
		ANALYSIS_HRESULT(D3D12CreateDevice(WARPAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_D3dDevice)));
	}

	//����Fence���� Ϊ��CPU��GPUͬ����׼��
	//D3D12_FENCE_FLAG_NONE 
	//D3D11_FENCE_FLAG_SHARED
	//D3D11_FENCE_FLAG_SHARED_CROSS_ADAPTER
	/*
	Fence->SetEventOnCompletion
	ִ������
	�ύ����
	Queue->Signal
	wait
	*/
	ANALYSIS_HRESULT(m_D3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));

	//��ʼ���������
////////////////////////////////////////////////////////////////////////////////////////
	//INT Priority 
	//D3D12_COMMAND_QUEUE_PRIORITY
	//D3D12_COMMAND_QUEUE_PRIORITY_NORMAL
	//D3D12_COMMAND_QUEUE_PRIORITY_HIGH
	//NodeMask ָʾ���������Ӧ���ĸ�GPU�ڵ���ִ��
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT;//ֱ��
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&m_commandQueue)));

	//	ID3D12CommandAllocator Allocator();
	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(m_commandAllocator.GetAddressOf())));

	ANALYSIS_HRESULT(m_D3dDevice->CreateCommandList(
		0, //Ĭ�ϵ���Gpu 
		D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT,//ֱ������
		m_commandAllocator.Get(),//��Commandlist������Allocator
		NULL,//ID3D12PipelineState
		IID_PPV_ARGS(m_commandList.GetAddressOf())));

	ANALYSIS_HRESULT(m_commandList->Close());

	//���ز���
////////////////////////////////////////////////////////////////////
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

	//������
////////////////////////////////////////////////////////////////////
	m_swapChain.Reset();
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc.Width = EngineRenderConfig::GetRenderConfig()->ScreenWidth;
	SwapChainDesc.BufferDesc.Height = EngineRenderConfig::GetRenderConfig()->ScreenHeight;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = EngineRenderConfig::GetRenderConfig()->RefreshRate;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferCount = EngineRenderConfig::GetRenderConfig()->SwapChainCount;
	//DXGI_USAGE_BACK_BUFFER //
	//DXGI_USAGE_READ_ONLY 
	//DXGI_USAGE_SHADER_INPUT
	//DXGI_USAGE_SHARED
	//DXGI_USAGE_UNORDERED_ACCESS
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;//ʹ�ñ������Դ��Ϊ�����ȾĿ�ꡣ
	SwapChainDesc.OutputWindow = MianWindowsHandle;//ָ��windows���
	SwapChainDesc.Windowed = true;//�Դ�������
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;//IDXGISwapChain::ResizeTarget
	SwapChainDesc.BufferDesc.Format = BackBufferFormat;//�����ʽ

	//���ز�������
	SwapChainDesc.SampleDesc.Count = GetDXGISampleCount();
	SwapChainDesc.SampleDesc.Quality = GetDXGISampleQuality();
	ANALYSIS_HRESULT(m_DXGIFactory->CreateSwapChain(
		m_commandQueue.Get(),
		&SwapChainDesc, m_swapChain.GetAddressOf()));

	//��Դ������
	////////////////////////////////////////////////////////////////////
	//D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV	//CBV������������ͼ SRV��ɫ����Դ��ͼ UAV���������ͼ
	//D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER		//��������ͼ
	//D3D12_DESCRIPTOR_HEAP_TYPE_RTV			//��ȾĿ�����ͼ��Դ
	//D3D12_DESCRIPTOR_HEAP_TYPE_DSV			//���/ģ�����ͼ��Դ
	//RTV
	D3D12_DESCRIPTOR_HEAP_DESC RTVDescriptorHeapDesc;
	RTVDescriptorHeapDesc.NumDescriptors = EngineRenderConfig::GetRenderConfig()->SwapChainCount;
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

	return false;
}

void DXRenderEngine::PostInitDirect3D()
{
	//ͬ��
	WaitGPUCommandQueueComplete();

	ANALYSIS_HRESULT(m_commandList->Reset(m_commandAllocator.Get(), NULL));

	for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
	{
		m_swapChainBuffer[i].Reset();
	}
	m_depthStencilBuffer.Reset();

	m_swapChain->ResizeBuffers(
		EngineRenderConfig::GetRenderConfig()->SwapChainCount,
		EngineRenderConfig::GetRenderConfig()->ScreenWidth,
		EngineRenderConfig::GetRenderConfig()->ScreenHeight,
		BackBufferFormat, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

	//�õ�����size
	RTVDescriptorSize = m_D3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE HeapHandle(m_RTVHeap->GetCPUDescriptorHandleForHeapStart());
	for (int i = 0; i < EngineRenderConfig::GetRenderConfig()->SwapChainCount; i++)
	{
		m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_swapChainBuffer[i]));
		m_D3dDevice->CreateRenderTargetView(m_swapChainBuffer[i].Get(), nullptr, HeapHandle);
		HeapHandle.Offset(1, RTVDescriptorSize);
	}

	D3D12_RESOURCE_DESC ResourceDesc;
	ResourceDesc.Width = EngineRenderConfig::GetRenderConfig()->ScreenWidth;
	ResourceDesc.Height = EngineRenderConfig::GetRenderConfig()->ScreenHeight;
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

	//��Щ�Ḳ��ԭ��windows����
	//�����ӿڳߴ�
	m_viewprotInfo.TopLeftX = 0;
	m_viewprotInfo.TopLeftY = 0;
	m_viewprotInfo.Width = EngineRenderConfig::GetRenderConfig()->ScreenWidth;
	m_viewprotInfo.Height = EngineRenderConfig::GetRenderConfig()->ScreenHeight;
	m_viewprotInfo.MinDepth = 0.f;
	m_viewprotInfo.MaxDepth = 1.f;

	//����
	m_viewprotRect.left = 0;
	m_viewprotRect.top = 0;
	m_viewprotRect.right = EngineRenderConfig::GetRenderConfig()->ScreenWidth;
	m_viewprotRect.bottom = EngineRenderConfig::GetRenderConfig()->ScreenHeight;

	WaitGPUCommandQueueComplete();
}

#endif