#include "RBuildTool.h"
#include "CodeReflection/CollectClassInfo/CollectClassInfo.h"
#include "CodeReflection/IntermediateFile/SpawnIntermediateFile.h"

int main()
{
		//生成反射代码的位置
		string CodeReflectionPath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineCodeReflectionPath());
		//要遍历的源文件位置
		string SourcePath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineSourcePath());

		//先移除所有反射代码
		remove_dir_all_files(CodeReflectionPath.c_str());

		def_c_paths Paths;
		init_def_c_paths(&Paths);

		find_files(SourcePath.c_str(), &Paths, true);

		for (int i = 0; i < Paths.index; i++)
		{
			if (find_string(Paths.paths[i], ".h", 0) != -1)
			{
				//单位化路径
				normalization_path(Paths.paths[i]);

				std::vector<std::string> StringArray;
				simple_cpp_helper_file::load_file_to_strings(Paths.paths[i], StringArray);

				if (IsCheckAllowCodeReflection(StringArray))
				{
					//收集类型
					ClassAnalysis ClassAnalysis;
					CollectClassInfo::Collection(Paths.paths[i], ClassAnalysis);

					//构建.h和.cpp代码
					std::vector<std::string> OutAnalysisRawH;
					std::vector<std::string> OutAnalysisRawCPP;
					IntermediateFile::Builder(ClassAnalysis, OutAnalysisRawH, OutAnalysisRawCPP);

					//C://dasd//asd//12.h
					char Buff[1024] = { 0 };
					get_path_clean_filename(Buff, Paths.paths[i]);

					remove_char_end(Buff, 'h');
					remove_char_end(Buff, '.');

					string PathH = CodeReflectionPath + "/" + Buff + ".CodeReflection.h";
					string PathCPP = CodeReflectionPath + "/" + Buff + ".CodeReflection.cpp";

					simple_cpp_helper_file::save_file_to_strings(PathH, OutAnalysisRawH);
					simple_cpp_helper_file::save_file_to_strings(PathCPP, OutAnalysisRawCPP);
				}
			}
		}
	return 0;
}