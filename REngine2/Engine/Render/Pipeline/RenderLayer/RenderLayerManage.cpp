#include"RenderLayerManage.h"
#include"RenderLayer.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../ConstontBuffer/ObjectTransformation.h"
#include"../../../Core/ViewPort/ViewportInfo.h"
RenderLayerManage::RenderLayerManage() 
{
	CreateRenderLayer<OpaqueLayer>();
	CreateRenderLayer<SkyLayer>();
}
void RenderLayerManage::RegisterRenderLayer(EMeshRenderLayerType type,std::shared_ptr<RenderLayer> renderLayer)
{
	m_RenderLayers.insert(make_pair(type, renderLayer));
}

std::shared_ptr<RenderLayer> RenderLayerManage::GetRenderLayerByType(EMeshRenderLayerType type)
{
	if (m_RenderLayers.find(type) != m_RenderLayers.end())
		return m_RenderLayers[type];
	return nullptr;
}

void RenderLayerManage::UpdateCalculations(const ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView)
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->UpdateCalculations(viewportInfo, objectConstantBufferView);
}

void RenderLayerManage::DrawMesh(map<int, RGeometry*> geometrys, ID3D12DescriptorHeap* heap, RConstantBufferView objectConstantBufferView)
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->DrawMesh(geometrys, heap, objectConstantBufferView);
}

std::map<EMeshRenderLayerType, std::shared_ptr<RenderLayer>> RenderLayerManage::GetAllRenderLayers() 
{ 
	return m_RenderLayers; 
}

void RenderLayerManage::SetPipelineState(RDXPipelineState* pipelineState)
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->SetPipelineState(pipelineState);
}

void RenderLayerManage::BuildPSO(UINT size) 
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.second->BuildPSO(size);
}