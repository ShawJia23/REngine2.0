#pragma once
#include"RenderLayerType.h"
#include"../../../Shader/Shader.h"
#include"../../../Shader/ShaderMacro.h"
#include"../../../Interface/DXDeviceInterface.h"
#include"../PipelineState/DXPipelineState.h"
struct ViewportInfo;
struct RConstantBufferView;
struct RRenderData;
struct RGeometry;
struct RGeometryMap;
class RenderLayer :public IDirectXDeviceInterface
{
public:
	RenderLayer();
	~RenderLayer();
	void InitRenderLayer(RDXPipelineState* inPipelineState, RGeometryMap* inGeometryMap);
	virtual void PostDraw();
public:
	void UpdateCalculations(ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView);
	virtual void DrawMesh();
	virtual void DrawMesh(std::weak_ptr<RRenderData>&  geometrys);
public:
	virtual void BuildShader()=0;
	virtual void BuildPSO();
	virtual void BuildShaderMacro(std::vector<RShaderMacro>& inMacro);
public:
	void  SetRenderLayerType(EMeshRenderLayerType type);
	void  AddRenderData(std::weak_ptr<RRenderData> data);
	void  RemoveRenderData(std::weak_ptr<RRenderData> data);
	void  Clear();
	EMeshRenderLayerType GetRenderLayerType() const;
	vector<std::weak_ptr<RRenderData>> GetRenderDatas();
	UINT GetRenderDataSize();
protected:
	RShader m_VertexShader;
	RShader m_PixelShader;
	vector<D3D12_INPUT_ELEMENT_DESC> m_InputElementDesc;
	RDXPipelineState* m_PipelineState;
private:
	RGeometryMap* m_GeometryMap;
	vector<std::weak_ptr<RRenderData>> m_RenderDatas;
	EMeshRenderLayerType RenderLayerType;
};