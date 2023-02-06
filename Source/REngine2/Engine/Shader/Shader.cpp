#include "Shader.h"

LPVOID RShader::GetBufferPointer() const
{
	return ShaderCode->GetBufferPointer();
}

SIZE_T RShader::GetBufferSize() const
{
	return ShaderCode->GetBufferSize();
}

void RShader::BuildShaders(const wstring& fileName, const string& entryFunName, const string& shadersVersion, const D3D_SHADER_MACRO* InShaderMacro)
{
	ComPtr<ID3DBlob> ErrorShaderMsg;
	HRESULT R = D3DCompileFromFile(fileName.c_str(),
		InShaderMacro, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryFunName.c_str(), shadersVersion.c_str(),
#if _DEBUG
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION
#else
		0
#endif
		, 0, &ShaderCode, &ErrorShaderMsg);

	if (ErrorShaderMsg)
	{
		Engine_Log_Error("%s", (char*)ErrorShaderMsg->GetBufferPointer());

		open_url(get_log_filename());
	}

	//Ê§°Ü¾Í±¼À£ÁË
	ANALYSIS_HRESULT(R);
}