#pragma once
#include "../EngineMinimal.h"

class RShader
{
public:
	LPVOID GetBufferPointer() const;
	SIZE_T GetBufferSize() const;

	void BuildShaders(const wstring& InFileName, const string& InEntryFunName, 
		const string& InShadersVersion, const D3D_SHADER_MACRO* InShaderMacro);
private:
	ComPtr<ID3DBlob> ShaderCode;
};