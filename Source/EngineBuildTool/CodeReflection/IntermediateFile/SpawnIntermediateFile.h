#pragma once

#include "../../RBuildTool.h"
#include "../CollectType.h"

namespace IntermediateFile
{
	bool Builder(
		const ClassAnalysis& InClassAnalysis,
		std::vector<std::string>& OutAnalysisRawH,
		std::vector<std::string>& OutAnalysisRawCPP);
} 