#pragma once
#include "DynamicMap.h"
#include "../RenderTarget/CubeMapRenderTarget.h"

struct ViewportInfo;
class RDXPipelineState;
class RenderLayerManage;
class RGeometryMap;
class ClientViewport;

class RDynamicCubeMap:public RDynamicMap
{
	typedef RDynamicMap Super;
public:
	RDynamicCubeMap();
	~RDynamicCubeMap();
	virtual void UpdateCalculations(const ViewportInfo& viewportInfo);
	virtual void Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDirectXPipelineState, RenderLayerManage* RenderManage);
	virtual void PreDraw();
	virtual void Draw();
protected:
	struct RTmpViewportCapture
	{
		RTmpViewportCapture() {}
		RTmpViewportCapture(const fvector_3d& InCenterPoint);

		fvector_3d TargetPoint[6];
		fvector_3d UP[6];

		void BuildViewportCapture(const fvector_3d& inCenterPoint);
	};
public:
	void SetViewportPosition(const fvector_3d& inPosition);
	virtual void BuildViewport(const fvector_3d& inCenterPoint);
	virtual void BuildDepthStencil();
	virtual void BuildRenderTargetDescriptor();

protected:
	virtual void BuildRenderTargetRTV();
	virtual void BuildRenderTargetSRV();

protected:

	CD3DX12_CPU_DESCRIPTOR_HANDLE DSVDes;//深度模板描述

	std::vector<ClientViewport*> CubeMapViewport;//6个视口

	ComPtr<ID3D12Resource> DepthStencilBuffer;
};
