#include"RenderLayerManage.h"
#include"RenderLayer.h"
#include"../Geometry/GeometryMap.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../ConstontBuffer/ObjectTransformation.h"
#include"../../../Core/ViewPort/ViewportInfo.h"
RenderLayerManage::RenderLayerManage() 
{
	CreateRenderLayer<OpaqueLayer>();
	CreateRenderLayer<SkyLayer>();
	CreateRenderLayer<SelectLayer>();
}

RenderLayerManage::~RenderLayerManage()
{

}


void RenderLayerManage::Init(RDXPipelineState* inPipelineState, RGeometryMap* inGeometryMap)
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->InitRenderLayer(inPipelineState, inGeometryMap);
}

void RenderLayerManage::RegisterRenderLayer(EMeshRenderLayerType type, std::shared_ptr<RenderLayer> renderLayer)
{
	m_RenderLayers.insert(make_pair(type, renderLayer));
}
void RenderLayerManage::BuildPSO()
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->BuildPSO();
}

void RenderLayerManage::DrawMesh()
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->DrawMesh();
}

void RenderLayerManage::UpdateCalculations(const ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView)
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->UpdateCalculations(viewportInfo, objectConstantBufferView);
}

void RenderLayerManage::PostDraw() 
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->PostDraw();
}

std::shared_ptr<RenderLayer> RenderLayerManage::GetRenderLayerByType(EMeshRenderLayerType type)
{
	if (m_RenderLayers.find(type) != m_RenderLayers.end())
		return m_RenderLayers[type];
	return nullptr;
}

std::map<EMeshRenderLayerType, std::shared_ptr<RenderLayer>> RenderLayerManage::GetAllRenderLayers() 
{ 
	return m_RenderLayers; 
}

void RenderLayerManage::Add(EMeshRenderLayerType layer, std::weak_ptr<RRenderData> renderData)
{
	if (auto nowLayer = GetRenderLayerByType(layer))
	{
		nowLayer->AddRenderData(renderData);
	}
}
void RenderLayerManage::Remove(EMeshRenderLayerType layer, std::weak_ptr<RRenderData> renderData)
{
	if (auto nowLayer = GetRenderLayerByType(layer))
	{
		nowLayer->RemoveRenderData(renderData);
	}
}

void RenderLayerManage::Clear(EMeshRenderLayerType layer)
{
	if (auto nowLayer = GetRenderLayerByType(layer))
	{
		nowLayer->Clear();
	}
}

void RenderLayerManage::HighlightDisplayObject(std::weak_ptr<RRenderData> renderData)
{
	//����ɵ�����
	Clear(EMeshRenderLayerType::RENDERLAYER_SELECT);

	//�����µ�
	Add(EMeshRenderLayerType::RENDERLAYER_SELECT, renderData);
}