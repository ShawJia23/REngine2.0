#include "ShaderMacro.h"

bool R2D3DShaderMacro(const vector<RShaderMacro>& inShaderMacro, vector<D3D_SHADER_MACRO>& outD3DMacro)
{
	for (auto& Tmp : inShaderMacro)
	{
		D3D_SHADER_MACRO ShaderMacro =
		{
			Tmp.Name.c_str(),
			Tmp.Definition.c_str(),
		};

		outD3DMacro.push_back(ShaderMacro);
	}

	if (outD3DMacro.size() > 0)
	{
		D3D_SHADER_MACRO ShaderMacro =
		{
			NULL,
			NULL,
		};

		outD3DMacro.push_back(ShaderMacro);
	}

	return outD3DMacro.size();
}
