#pragma once
#include "DynamicMap.h"
#include "../RenderTarget/CubeMapRenderTarget.h"

struct ViewportInfo;
class RDXPipelineState;
class RGeometryMap;
class RenderLayerManage;
class ClientViewport;

class RDynamicCubeMap :public RDynamicMap
{
	typedef RDynamicMap Super;
protected:
	struct RTmpViewportCapture
	{
		RTmpViewportCapture() {}
		~RTmpViewportCapture() {}
		RTmpViewportCapture(const fvector_3d& inCenterPoint);

		fvector_3d TargetPoint[6];
		fvector_3d UP[6];

		void BuildViewportCapture(const fvector_3d& inCenterPoint);
	};
public:
	RDynamicCubeMap();
	~RDynamicCubeMap();
	virtual void Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDirectXPipelineState, RenderLayerManage* inRenderLayer);

	void SetViewportPosition(const fvector_3d& inPosition);
	virtual void BuildViewport(const fvector_3d& inCenterPoint);

protected:
	virtual void BuildRenderTargetRTV() {}
	virtual void BuildRenderTargetSRV() {}
public:
	virtual void BuildDepthStencil();
	virtual void BuildRenderTargetDescriptor();

protected:

	CD3DX12_CPU_DESCRIPTOR_HANDLE DSVDes;//深度模板描述

	std::vector<ClientViewport*> CubeMapViewport;//6个视口

	ComPtr<ID3D12Resource> DepthStencilBuffer;
};
