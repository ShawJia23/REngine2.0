#include "CubeMapRenderTarget.h"
#include"../../Engine/DXRenderEngine.h"
RCubeMapRenderTarget::RCubeMapRenderTarget()
	:Super()
{
	CPURenderTargetView.resize(6);
}

RCubeMapRenderTarget::~RCubeMapRenderTarget()
{
	
}

void RCubeMapRenderTarget::Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat)
{
	Super::Init(inWidth, inHeight, inFormat);

}

CD3DX12_CPU_DESCRIPTOR_HANDLE& RCubeMapRenderTarget::GetCPURenderTargetView(int Index)
{
	return CPURenderTargetView[Index];
}

void RCubeMapRenderTarget::BuildRenderTargetMap()
{
	D3D12_RESOURCE_DESC ResourceDesc;
	memset(&ResourceDesc, 0, sizeof(ResourceDesc));

	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	ResourceDesc.Alignment = 0;
	ResourceDesc.Width = Width;
	ResourceDesc.Height = Height;
	ResourceDesc.DepthOrArraySize = 6;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.Format = Format;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.SampleDesc.Quality = 0;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	ResourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

	CD3DX12_HEAP_PROPERTIES BufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	ANALYSIS_HRESULT(DXRenderEngine::getInstance().GetD3dDevice()->CreateCommittedResource(
		&BufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_COMMON,
		NULL, IID_PPV_ARGS(RenderTargetMap.GetAddressOf())));
}

void RCubeMapRenderTarget::BuildRTVDescriptors()
{
	for (size_t i = 0; i < 6; i++)
	{
		D3D12_RENDER_TARGET_VIEW_DESC RTVDesc = { };
		RTVDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2DARRAY;
		RTVDesc.Format = Format;
		RTVDesc.Texture2DArray.MipSlice = 0;
		RTVDesc.Texture2DArray.PlaneSlice = 0;
		//MipSlice + ArraySlice * MipLevels
		RTVDesc.Texture2DArray.FirstArraySlice = i;
		RTVDesc.Texture2DArray.ArraySize = 1;

		DXRenderEngine::getInstance().GetD3dDevice()->CreateRenderTargetView(
			RenderTargetMap.Get(),
			&RTVDesc,
			CPURenderTargetView[i]);
	}
}

void RCubeMapRenderTarget::BuildSRVDescriptors()
{
	D3D12_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	SRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	SRVDesc.Format = Format;
	SRVDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;

	SRVDesc.TextureCube.MostDetailedMip = 0;
	SRVDesc.TextureCube.MipLevels = 1;
	SRVDesc.TextureCube.ResourceMinLODClamp = 0.f;

	DXRenderEngine::getInstance().GetD3dDevice()->CreateShaderResourceView(
		RenderTargetMap.Get(),
		&SRVDesc,
		CPUShaderResourceView);
}