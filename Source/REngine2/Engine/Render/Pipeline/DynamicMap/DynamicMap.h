#pragma once
#include "../RenderTarget/RenderTarget.h"

struct ViewportInfo;
class RDXPipelineState;
class RGeometryMap;
class RenderLayerManage;
class RDynamicMap
{
public:
	RDynamicMap();
	~RDynamicMap();
public:
	virtual void UpdateCalculations(float deltaTime, const ViewportInfo& viewportInfo);
	virtual void Init(RGeometryMap* inGeometryMap, RDXPipelineState* inDirectXPipelineState, RenderLayerManage* inRenderLayer);
	virtual void Init(int inWidth, int inHeight);
	virtual void PreDraw(float deltaTime);
	virtual void Draw(float deltaTime);

	virtual void BuildSRVOffset();
	virtual void BuildRTVOffset();
public:
	template<class T>
	void CreateRenderTarget();

	std::shared_ptr<RRenderTarget> GetRenderTarget() const { return RenderTarget; }

public:

	void SetSRVOffset(UINT InOffset) { SRVOffset = InOffset; }
	UINT GetSRVOffset() { return SRVOffset; }

	void SetRTVOffset(UINT InOffset) { RTVOffset = InOffset; }
	UINT GetRTVOffset() { return RTVOffset; }

	UINT GetWidth()const { return Width; }
	UINT GetHeight()const { return Height; }
protected:
	RGeometryMap* GeometryMap;//几何Map
	RDXPipelineState* DirectXPipelineState;//管线对象 用于绑定

	RenderLayerManage* RenderLayer;//渲染层级

	UINT Width;
	UINT Height;

	UINT SRVOffset;//绑定到Shader寄存器
	UINT RTVOffset;//渲染目标的偏移

	std::shared_ptr<RRenderTarget> RenderTarget;//渲染目标
};

template<class T>
void RDynamicMap::CreateRenderTarget()
{
	if (!RenderTarget)
	{
		RenderTarget = std::make_shared<T>();
	}
}
