#include "DynamicCubeMap.h"
#include "../Geometry/GeometryMap.h"
#include"../PipelineState/DXPipelineState.h"
#include"../../../ViewPort/ClientViewport.h"
#include"../../../ViewPort/ViewportInfo.h"
#include "../RenderLayer/RenderLayerManage.h"
#include"../../../Config/RenderConfig.h"
#include"../../../Component/Mesh/MeshComponent.h"
#include"../../Engine/DXRenderEngine.h"
#include"../../../Config/RenderConfig.h"
RDynamicCubeMap::RDynamicCubeMap()
	:Super()
{
	CreateRenderTarget<RCubeMapRenderTarget>();
}

RDynamicCubeMap::~RDynamicCubeMap()
{

}

void RDynamicCubeMap::UpdateCalculations(const ViewportInfo& viewportInfo)
{
	if (CubeMapViewport.size() == 6)
	{
		for (int i = 0; i < GeometryMap->DynamicReflectionMeshComponents.size(); i++)
		{
			RMeshComponent* Tmp = GeometryMap->DynamicReflectionMeshComponents[i];
			XMFLOAT3 F3 = Tmp->GetPosition();
			SetViewportPosition(fvector_3d(F3.x, F3.y, F3.z));

			for (size_t j = 0; j < 6; j++)
			{
				ViewportInfo MyViewportInfo;

				XMFLOAT3 ViewPosition = CubeMapViewport[j]->GetPosition();
				MyViewportInfo.ViewportPosition = XMFLOAT4(ViewPosition.x, ViewPosition.y, ViewPosition.z, 1.f);
				MyViewportInfo.ViewMatrix = CubeMapViewport[j]->ViewMatrix;
				MyViewportInfo.ProjectMatrix = CubeMapViewport[j]->ProjectMatrix;

				GeometryMap->UpdateCalculationsViewport(MyViewportInfo,
					j + i * 6 +//给动态摄像机
					1);//给主视口
			}
		}
	}

}

void RDynamicCubeMap::Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDirectXPipelineState, RenderLayerManage* renderManage)
{
	Super::Init(inGeometryMap, inDirectXPipelineState, renderManage);
}

void RDynamicCubeMap::PreDraw()
{
	auto cmdList = DXRenderEngine::getInstance().GetCommandList();
	for (int j = 0; j < GeometryMap->DynamicReflectionMeshComponents.size(); j++)
	{
		//指向哪个资源 转换其状态
		CD3DX12_RESOURCE_BARRIER ResourceBarrierPresent = CD3DX12_RESOURCE_BARRIER::Transition(
			RenderTarget->GetRenderTarget(),
			D3D12_RESOURCE_STATE_GENERIC_READ, D3D12_RESOURCE_STATE_RENDER_TARGET);

		cmdList->ResourceBarrier(1, &ResourceBarrierPresent);

		//需要每帧执行
		//绑定矩形框
		auto RenderTargetViewport = RenderTarget->GetViewport();
		auto RenderTargetScissorRect = RenderTarget->GetScissorRect();
		cmdList->RSSetViewports(1, &RenderTargetViewport);
		cmdList->RSSetScissorRects(1, &RenderTargetScissorRect);

		UINT CBVSize = GeometryMap->GetViewportConstantBufferView().GetConstantBufferByteSize();
		for (size_t i = 0; i < 6; i++)
		{
			auto pPtr= std::dynamic_pointer_cast<RCubeMapRenderTarget>(RenderTarget);
			//清除画布
			cmdList->ClearRenderTargetView(
				pPtr->CPURenderTargetView[i],
				DirectX::Colors::Black,
				0, nullptr);

			//清除深度模板缓冲区
			cmdList->ClearDepthStencilView(
				DSVDes,
				D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
				1.f, 0, 0, NULL);

			//输出的合并阶段
			cmdList->OMSetRenderTargets(1,
				&pPtr->CPURenderTargetView[i],
				true,
				&DSVDes);

			//更新6个摄像机 绑定6个摄像机
			auto ViewprotAddr = GeometryMap->GetViewportConstantBufferView().GetBuffer()->GetGPUVirtualAddress();
			ViewprotAddr += (
				1 + //主摄像机
				i + j * 6 //
				) * CBVSize;

			cmdList->SetGraphicsRootConstantBufferView(1, ViewprotAddr);

			//各类层级渲染
			RenderLayer->DrawMesh();
		}

		CD3DX12_RESOURCE_BARRIER ResourceBarrierPresentRenderTarget = CD3DX12_RESOURCE_BARRIER::Transition(
			RenderTarget->GetRenderTarget(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_GENERIC_READ);

		cmdList->ResourceBarrier(1, &ResourceBarrierPresentRenderTarget);

		DXRenderEngine::getInstance().StartSetMainViewportRenderTarget();

		//主视口
		Draw();

		//RenderLayer->FindObjectDraw(
		//	DeltaTime,
		//	RENDERLAYER_OPAQUE_REFLECTOR,
		//	GeometryMap->DynamicReflectionMeshComponents[j]);

		//重置CubeMap
		GeometryMap->DrawTexture();

		//End
		DXRenderEngine::getInstance().EndSetMainViewportRenderTarget();
	}
}

void RDynamicCubeMap::Draw()
{
	DXRenderEngine::getInstance().GetCommandList()->SetGraphicsRootDescriptorTable(5, RenderTarget->GetGPUSRVOffset());
}

void RDynamicCubeMap::SetViewportPosition(const fvector_3d& inCenterPoint)
{
	//捕获摄像机四个面
	RTmpViewportCapture Capture(inCenterPoint);

	for (size_t i = 0; i < 6; i++)
	{
		CubeMapViewport[i]->SetPosition(XMFLOAT3(inCenterPoint.x, inCenterPoint.y, inCenterPoint.z));
		CubeMapViewport[i]->FaceTarget(inCenterPoint, Capture.TargetPoint[i], Capture.UP[i]);
		CubeMapViewport[i]->BuildViewMatrix();
	}
}

void RDynamicCubeMap::BuildViewport(const fvector_3d& inCenterPoint)
{
	//捕获摄像机四个面
	RTmpViewportCapture Capture(inCenterPoint);

	for (size_t i = 0; i < 6; i++)
	{
		CubeMapViewport.push_back(CreateObject<ClientViewport>(CreateObjectParam(), new ClientViewport()));
		ClientViewport* Viewport = CubeMapViewport[CubeMapViewport.size() - 1];

		Viewport->SetPosition(XMFLOAT3(inCenterPoint.x, inCenterPoint.y, inCenterPoint.z));
		Viewport->FaceTarget(inCenterPoint, Capture.TargetPoint[i], Capture.UP[i]);
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

	UINT DescriptorHandleIncrementSize = DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	DSVDes = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		DXRenderEngine::getInstance().GetCurrentDepthStencilView(),
		1,
		DescriptorHandleIncrementSize);

	DXRenderEngine::getInstance().GetD3dDevice()->CreateDepthStencilView(DepthStencilBuffer.Get(), NULL, DSVDes);

	CD3DX12_RESOURCE_BARRIER Barrier = CD3DX12_RESOURCE_BARRIER::Transition(DepthStencilBuffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_DEPTH_WRITE);

	DXRenderEngine::getInstance().GetCommandList()->ResourceBarrier(1, &Barrier);
}

void RDynamicCubeMap::BuildRenderTargetDescriptor()
{
	//视图
	BuildRenderTargetRTV();

	//给Shader
	BuildRenderTargetSRV();

	//初始化Target
	RenderTarget->Init(Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM);
}

void RDynamicCubeMap::BuildRenderTargetRTV()
{
	UINT RTVDescriptorSize = DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	//RTV的起始
	auto RTVDesHeapStart = DXRenderEngine::getInstance().GetRTVHeap()->GetCPUDescriptorHandleForHeapStart();

	if (RCubeMapRenderTarget* InRenderTarget = dynamic_cast<RCubeMapRenderTarget*>(RenderTarget.get()))
	{
		//偏移的地址记录
		for (size_t i = 0; i < 6; i++)
		{
			InRenderTarget->GetCPURenderTargetView(i) = CD3DX12_CPU_DESCRIPTOR_HANDLE(
				RTVDesHeapStart,
				EngineRenderConfig::GetRenderConfig()->SwapChainCount
				+ i,//cube
				RTVDescriptorSize);
		}
	}
}

void RDynamicCubeMap::BuildRenderTargetSRV()
{
	UINT CBVDescriptorSize = DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto CPUSRVDesHeapStart = GeometryMap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	auto GPUSRVDesHeapStart = GeometryMap->GetHeap()->GetGPUDescriptorHandleForHeapStart();

	int Offset =
		GeometryMap->GetTextureNumber() +
		GeometryMap->GetCubeMapNumber() +
		1;//cube

	if (RCubeMapRenderTarget* InRenderTarget = dynamic_cast<RCubeMapRenderTarget*>(RenderTarget.get()))
	{
		InRenderTarget->GetCPUSRVOffset() =
			CD3DX12_CPU_DESCRIPTOR_HANDLE(CPUSRVDesHeapStart,
				Offset,
				CBVDescriptorSize);

		InRenderTarget->GetGPUSRVOffset() =
			CD3DX12_GPU_DESCRIPTOR_HANDLE(GPUSRVDesHeapStart,
				Offset,
				CBVDescriptorSize);
	}
}

RDynamicCubeMap::RTmpViewportCapture::RTmpViewportCapture(const fvector_3d& InCenterPoint)
{
	BuildViewportCapture(InCenterPoint);
}

void RDynamicCubeMap::RTmpViewportCapture::BuildViewportCapture(const fvector_3d& InCenterPoint)
{
	//捕获摄像机四个面
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

