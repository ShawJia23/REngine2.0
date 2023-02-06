#pragma once
#include"../EngineMinimal.h"

struct RShaderMacro
{
	std::string Name;
	std::string Definition;
};

bool R2D3DShaderMacro(const vector<RShaderMacro>& inShaderMacro, vector<D3D_SHADER_MACRO>& outD3DMacro);
