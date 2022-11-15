#pragma once
#include"RenderLayer.h"

class RenderLayerManage 
{
public:
	RenderLayerManage();
	void ResetCommandList();
	void BuildPipelineState(UINT TextureSize, ID3D12RootSignature* rootSignature);
	void CaptureKeyboardKeys();
	void RegisterRenderLayer(EMeshRenderLayerType type, std::shared_ptr<RenderLayer> renderLayer);
public:
	std::shared_ptr<RenderLayer> GetRenderLayerByType(EMeshRenderLayerType type);
	std::map<EMeshRenderLayerType, std::shared_ptr<RenderLayer>> GetAllRenderLayers();
public:
	void UpdateCalculations(ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView);
	void DrawMesh(map<int, RGeometry*> geometrys, ID3D12DescriptorHeap* heap);
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