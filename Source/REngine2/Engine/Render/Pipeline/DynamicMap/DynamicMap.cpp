#include "DynamicMap.h"
#include"../Geometry/GeometryMap.h"
#include"../../Engine/DXRenderEngine.h"
RDynamicMap::RDynamicMap()
	: GeometryMap(NULL)
	, DirectXPipelineState(NULL)
	, RenderLayer(NULL)
	, Width(256)
	, Height(256)
	, SRVOffset(0)
	, RTVOffset(0)
{

}
RDynamicMap::~RDynamicMap() 
{

}


void RDynamicMap::UpdateCalculations(const ViewportInfo& viewportInfo)
{

}

void RDynamicMap::Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDXPipelineState, RenderLayerManage* inRenderLayer)
{
	GeometryMap = inGeometryMap;
	DirectXPipelineState = inDXPipelineState;
	RenderLayer = inRenderLayer;
}

void RDynamicMap::PreDraw(float deltaTime)
{

}

void RDynamicMap::Draw(float deltaTime)
{

}

void RDynamicMap::BuildSRVOffset()
{
	UINT CBVDescriptorSize = DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto CPUSRVDesHeapStart = GeometryMap->GetHeap()->GetCPUDescriptorHandleForHeapStart();
	auto GPUSRVDesHeapStart = GeometryMap->GetHeap()->GetGPUDescriptorHandleForHeapStart();

	int Offset = GetSRVOffset();

	RenderTarget->GetCPUSRVOffset() =
		CD3DX12_CPU_DESCRIPTOR_HANDLE(CPUSRVDesHeapStart,
			Offset,
			CBVDescriptorSize);

	RenderTarget->GetGPUSRVOffset() =
		CD3DX12_GPU_DESCRIPTOR_HANDLE(GPUSRVDesHeapStart,
			Offset,
			CBVDescriptorSize);
}

void RDynamicMap::BuildRTVOffset()
{
	RenderTarget.get()->GetCPURenderTargetView() =
		CD3DX12_CPU_DESCRIPTOR_HANDLE(
			DXRenderEngine::getInstance().GetRTVHeap()->GetCPUDescriptorHandleForHeapStart(),
			GetRTVOffset(),
			DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV));
}

void RDynamicMap::Init(int inWidth, int inHeight)
{
	Width = inWidth;
	Height = inHeight;
}
