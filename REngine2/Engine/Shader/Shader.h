#pragma once
#include "../EngineMinimal.h"

class RShader
{
public:
	LPVOID GetBufferPointer();
	SIZE_T GetBufferSize();

	void BuildShaders(const wstring& InFileName, const string& InEntryFunName, const string& InShadersVersion);
private:
	ComPtr<ID3DBlob> ShaderCode;
};