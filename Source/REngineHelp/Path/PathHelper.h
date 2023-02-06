#pragma once
#include "../REngineHelperMacro.h"
#include "../REngineHelper.h"

struct RENGINECORE_API PathHelper
{
	static std::string GetEngineRootPath();

	static std::string GetEngineBinariesPath();

	static std::string GetEngineLogsPath();

	static std::string GetEngineSourcePath();

	static std::string GetEngineIntermediatePath();

	static std::string GetEngineCodeReflectionPath();

	static std::string GetEngineContentPath();

	static std::wstring GetEngineShadersPath();

	static std::string RelativeToAbsolutePath(const std::string& InPath);
};