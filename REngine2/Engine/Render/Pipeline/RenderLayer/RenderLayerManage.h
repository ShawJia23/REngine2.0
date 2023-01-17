#pragma once
#include"RenderLayer.h"

class GActorObject;
class RComponent;
class RenderLayerManage 
{
public:
	RenderLayerManage();
	~RenderLayerManage();

	void Init(RDXPipelineState* inPipelineState, RGeometryMap* inGeometryMap);
	void RegisterRenderLayer(EMeshRenderLayerType type, std::shared_ptr<RenderLayer> renderLayer);
	void BuildPSO();
	void PostDraw();
public:
	void DrawMesh();
	void UpdateCalculations(ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView);

public:
	std::shared_ptr<RenderLayer> GetRenderLayerByType(EMeshRenderLayerType type);
	std::map<EMeshRenderLayerType, std::shared_ptr<RenderLayer>> GetAllRenderLayers();
public:
	void Add(EMeshRenderLayerType layer, std::weak_ptr<RRenderData> renderData);
	void Remove(EMeshRenderLayerType layer, std::weak_ptr<RRenderData> renderData);
	void Clear(EMeshRenderLayerType layer);
public:
	virtual void HighlightDisplayObject(std::weak_ptr<RRenderData> renderData);
public:
	template<class T>
	void  CreateRenderLayer()
	{
		std::shared_ptr<T> RenderLayer = std::make_shared<T>();
		RegisterRenderLayer(RenderLayer->GetRenderLayerType(), RenderLayer);
	}
private:
	std::map<EMeshRenderLayerType, std::shared_ptr<RenderLayer>>m_RenderLayers;
};