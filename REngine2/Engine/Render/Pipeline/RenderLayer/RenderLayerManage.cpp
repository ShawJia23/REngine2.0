#include"RenderLayerManage.h"

RenderLayerManage::RenderLayerManage() 
{

}
void RenderLayerManage::ResetCommandList() 
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.ResetCommandList();
}
void RenderLayerManage::BuildPipelineState(UINT TextureSize, ID3D12RootSignature* rootSignature) 
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.BuildPipelineState(TextureSize, rootSignature);
}
void RenderLayerManage::CaptureKeyboardKeys() 
{
	for (auto& Tmp : m_RenderLayers)
		Tmp.CaptureKeyboardKeys();
}