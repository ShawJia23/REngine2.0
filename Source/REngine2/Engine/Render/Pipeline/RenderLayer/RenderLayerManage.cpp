#include"RenderLayerManage.h"
#include"RenderLayerMinimal.h"
#include"../Geometry/GeometryMap.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../ConstontBuffer/ObjectTransformation.h"
#include"../../../ViewPort/ViewportInfo.h"
#include"../../../Component/RComponentMinimal.h"
#include"../../../Actor/ActorObject.h"
#include"../../../World.h"

extern GActorObject* SelectedObject;
RenderLayerManage::RenderLayerManage() 
{
	CreateRenderLayer<OpaqueLayer>();
	CreateRenderLayer<SkyLayer>();
	CreateRenderLayer<SelectLayer>();
	CreateRenderLayer<PositionHandleLayer>();
	CreateRenderLayer<RotateHandleLayer>();
	CreateRenderLayer<OpaqueReflectorRenderLayer>();
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

extern int SelectedVariable;
void RenderLayerManage::HighlightDisplayObject(std::weak_ptr<RRenderData> renderData)
{
#if EDITOR_ENGINE
	//清除旧的物体
	Clear(EMeshRenderLayerType::RENDERLAYER_SELECT);

	//设置新的
	Add(EMeshRenderLayerType::RENDERLAYER_SELECT, renderData);

	if (GActorObject* pActor = dynamic_cast<GActorObject*>(renderData.lock()->Mesh->GetOuter()))
	{
		auto actors = RWorld::getInstance().GetActors();
		for (size_t i = 0; i < actors.size(); i++)
		{
			if (actors[i] == pActor)
			{
				SelectedVariable = i;
				SelectedObject = pActor;
				break;
			}
		}
	}
#endif 
}