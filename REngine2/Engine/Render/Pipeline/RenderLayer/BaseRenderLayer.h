#pragma once
#include"RenderLayerType.h"
#include"../../../Shader/Shader.h"
#include"../../../Interface/DXDeviceInterface.h"
#include"../PipelineState/DXPipelineState.h"
struct ViewportInfo;
struct RConstantBufferView;
struct RRenderData;
struct RGeometry;
class RenderLayer :public IDirectXDeviceInterface
{
public:
	RenderLayer();
	void SetPipelineState(RDXPipelineState* pipelineState);
public:
	void UpdateCalculations(ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView);
	void DrawMesh(map<int, RGeometry*> geometrys, ID3D12DescriptorHeap* heap);
public:
	virtual void BuildShader(UINT TextureSize)=0;
	virtual void BuildPSO(UINT size);
public:
	void  SetRenderLayerType(EMeshRenderLayerType type);
	void  AddRenderData(RRenderData* data);

	EMeshRenderLayerType GetRenderLayerType() const;
	vector<RRenderData*> GetRenderDatas();
	UINT GetRenderDataSize();
protected:
	RShader m_VertexShader;
	RShader m_PixelShader;
	vector<D3D12_INPUT_ELEMENT_DESC> m_InputElementDesc;
	RDXPipelineState* m_PipelineState;
private:
	vector<RRenderData*> m_RenderDatas;
	EMeshRenderLayerType RenderLayerType;
};