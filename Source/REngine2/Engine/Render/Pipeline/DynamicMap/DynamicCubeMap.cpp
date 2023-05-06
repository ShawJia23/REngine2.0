#include "DynamicCubeMap.h"
#include"../../../ViewPort/ClientViewport.h"
#include"../../Engine/DXRenderEngine.h"
RDynamicCubeMap::RDynamicCubeMap()
	:Super()
{
	CreateRenderTarget<RCubeMapRenderTarget>();
}

RDynamicCubeMap::~RDynamicCubeMap()
{

}

void RDynamicCubeMap::Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDXPipelineState, RenderLayerManage* inRenderLayer)
{
	Super::Init(inGeometryMap, inDXPipelineState, inRenderLayer);
}

void RDynamicCubeMap::SetViewportPosition(const fvector_3d& InCenterPoint)
{
	//����������ĸ���
	RTmpViewportCapture Capture(InCenterPoint);

	for (size_t i = 0; i < 6; i++)
	{
		CubeMapViewport[i]->SetPosition(XMFLOAT3(InCenterPoint.x, InCenterPoint.y, InCenterPoint.z));
		CubeMapViewport[i]->FaceTarget(InCenterPoint, Capture.TargetPoint[i], Capture.UP[i]);
		CubeMapViewport[i]->BuildViewMatrix();
	}
}

void RDynamicCubeMap::BuildViewport(const fvector_3d& InCenterPoint)
{
	//����������ĸ���
	RTmpViewportCapture Capture(InCenterPoint);

	for (size_t i = 0; i < 6; i++)
	{
		CubeMapViewport.push_back(CreateObject<ClientViewport>(CreateObjectParam(), new ClientViewport()));
		ClientViewport* Viewport = CubeMapViewport[CubeMapViewport.size() - 1];

		Viewport->SetPosition(XMFLOAT3(InCenterPoint.x, InCenterPoint.y, InCenterPoint.z));
		Viewport->FaceTarget(InCenterPoint, Capture.TargetPoint[i], Capture.UP[i]);
		Viewport->SetFrustum(0.5f * XM_PI, 1.f, 0.1f, 10000.f);
		Viewport->BuildViewMatrix();

		Viewport->ViewprotInfo = RenderTarget->GetViewport();
		Viewport->ViewprotRect = RenderTarget->GetScissorRect();
	}
}

void RDynamicCubeMap::BuildDepthStencil()
{
	D3D12_RESOURCE_DESC ResourceDesc;
	ResourceDesc.Width = Width;
	ResourceDesc.Height = Height;
	ResourceDesc.Alignment = 0;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.SampleDesc.Quality = 0;
	ResourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	D3D12_CLEAR_VALUE ClearValue;
	ClearValue.DepthStencil.Depth = 1.f;
	ClearValue.DepthStencil.Stencil = 0;
	ClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	CD3DX12_HEAP_PROPERTIES Properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	DXRenderEngine::getInstance().GetD3dDevice()->CreateCommittedResource(
		&Properties,
		D3D12_HEAP_FLAG_NONE, &ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON, &ClearValue,
		IID_PPV_ARGS(DepthStencilBuffer.GetAddressOf()));

	DXRenderEngine::getInstance().GetD3dDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), NULL, DSVDes);

	CD3DX12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE);

	DXRenderEngine::getInstance().GetCommandList()->ResourceBarrier(1, &Barrier);
}

void RDynamicCubeMap::BuildRenderTargetDescriptor()
{
	//��ͼ
	BuildRenderTargetRTV();

	//��Shader
	BuildRenderTargetSRV();

	//��ʼ��Target
	RenderTarget->Init(Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM);
}

void RDynamicCubeMap::RTmpViewportCapture::BuildViewportCapture(const fvector_3d& InCenterPoint)
{
	//����������ĸ���
	TargetPoint[0] = fvector_3d(InCenterPoint.x + 1.0f, InCenterPoint.y, InCenterPoint.z);
	TargetPoint[1] = fvector_3d(InCenterPoint.x - 1.0f, InCenterPoint.y, InCenterPoint.z);
	TargetPoint[2] = fvector_3d(InCenterPoint.x, InCenterPoint.y + 1.0f, InCenterPoint.z);
	TargetPoint[3] = fvector_3d(InCenterPoint.x, InCenterPoint.y - 1.0f, InCenterPoint.z);
	TargetPoint[4] = fvector_3d(InCenterPoint.x, InCenterPoint.y, InCenterPoint.z + 1.0f);
	TargetPoint[5] = fvector_3d(InCenterPoint.x, InCenterPoint.y, InCenterPoint.z - 1.0f);

	UP[0] = fvector_3d(0.f, 1.f, 0.f);
	UP[1] = fvector_3d(0.f, 1.f, 0.f);
	UP[2] = fvector_3d(0.f, 0.f, -1.f);
	UP[3] = fvector_3d(0.f, 0.f, 1.f);
	UP[4] = fvector_3d(0.f, 1.f, 0.f);
	UP[5] = fvector_3d(0.f, 1.f, 0.f);
}

