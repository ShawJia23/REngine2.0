#pragma once
#include "RenderTarget.h"

//提供渲染内容的接口
class RCubeMapRenderTarget :public RRenderTarget
{
	typedef RRenderTarget Super;
	friend class FDynamicCubeMap;
public:
	RCubeMapRenderTarget();
	~RCubeMapRenderTarget();
	virtual void Init(UINT inWidth, UINT inHeight, DXGI_FORMAT inFormat);

public:
	CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCPURenderTargetView(int index);
private:
	virtual void BuildRenderTargetMap();
	virtual void BuildSRVDescriptors();
	virtual void BuildRTVDescriptors();

private:
	//RTV
	std::vector<CD3DX12_CPU_DESCRIPTOR_HANDLE> CPURenderTargetView;
};