#include"OpaqueReflectorRenderLayer.h"

OpaqueReflectorRenderLayer::OpaqueReflectorRenderLayer()
{
	SetRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE_REFLECTOR);
}

void OpaqueReflectorRenderLayer::BuildShader()
{
	vector<RShaderMacro> ShaderMacro;
	BuildShaderMacro(ShaderMacro);

	vector<D3D_SHADER_MACRO> D3DShaderMacro;
	R2D3DShaderMacro(ShaderMacro, D3DShaderMacro);
	wstring pStr = PathHelper::GetEngineShadersPath() + L"/Default.hlsl";

	m_VertexShader.BuildShaders(pStr, "VertexShaderMain", "vs_5_1", D3DShaderMacro.data());
	m_PixelShader.BuildShaders(pStr, "PixelShaderMain", "ps_5_1", D3DShaderMacro.data());
	m_PipelineState->BindShader(m_VertexShader, m_PixelShader);

	m_InputElementDesc =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 52, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
	m_PipelineState->BindInputLayout(m_InputElementDesc.data(), m_InputElementDesc.size());
}

void OpaqueReflectorRenderLayer::BuildPSO()
{
	Super::BuildPSO();

	m_PipelineState->CreatePSO((int)GetRenderLayerType());
}