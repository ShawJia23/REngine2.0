#include "PathHelper.h"

std::string PathHelper::GetEngineRootPath()
{
	return string();
}

std::string PathHelper::GetEngineBinariesPath()
{
	return "..\\Binaries\\Win64";
}

std::string PathHelper::GetEngineLogsPath()
{
	return "..\\Saved\\Logs";
}

std::string PathHelper::GetEngineSourcePath()
{
	return "..\\..\\Source";
}

std::string PathHelper::GetEngineIntermediatePath()
{
	return "..\\Intermediate";
}

std::string PathHelper::GetEngineCodeReflectionPath()
{
	return "..\\..\\Intermediate\\CodeReflection";
}

std::string PathHelper::GetEngineContentPath()
{
	return "..\\..\\Content";
}

std::wstring PathHelper::GetEngineShadersPath()
{
	return L"..\\..\\Shaders";
}

std::string PathHelper::RelativeToAbsolutePath(const std::string& InPath)
{
	char PathBuff[1024] = { 0 };
	get_full_path(PathBuff, 1024, InPath.c_str());

	return PathBuff;
}
