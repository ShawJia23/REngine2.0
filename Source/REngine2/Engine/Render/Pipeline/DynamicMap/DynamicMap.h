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
	RGeometryMap* GeometryMap;//����Map
	RDXPipelineState* DirectXPipelineState;//���߶��� ���ڰ�

	RenderLayerManage* RenderLayer;//��Ⱦ�㼶

	UINT Width;
	UINT Height;

	UINT SRVOffset;//�󶨵�Shader�Ĵ���
	UINT RTVOffset;//��ȾĿ���ƫ��

	std::shared_ptr<RRenderTarget> RenderTarget;//��ȾĿ��
};

template<class T>
void RDynamicMap::CreateRenderTarget()
{
	if (!RenderTarget)
	{
		RenderTarget = std::make_shared<T>();
	}
}
