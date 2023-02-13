#include "RBuildTool.h"
#include "CodeReflection/CollectClassInfo/CollectClassInfo.h"
#include "CodeReflection/IntermediateFile/SpawnIntermediateFile.h"

int main()
{
		//���ɷ�������λ��
		string CodeReflectionPath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineCodeReflectionPath());
		//Ҫ������Դ�ļ�λ��
		string SourcePath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineSourcePath());

		//���Ƴ����з������
		remove_dir_all_files(CodeReflectionPath.c_str());

		def_c_paths Paths;
		init_def_c_paths(&Paths);

		find_files(SourcePath.c_str(), &Paths, true);

		map<string, vector<string>> Modulars;
		for (int i = 0; i < Paths.index; i++)
		{
			if (find_string(Paths.paths[i], ".vcxproj", 0) != -1)
			{
				//��λ��·��
				normalization_path(Paths.paths[i]);

				char Buff[1024] = { 0 };
				get_path_directory(Buff, Paths.paths[i]);

				Modulars.insert(make_pair(Buff, vector<string>()));
			}
		}
		for (int i = 0; i < Paths.index; i++)
		{
			if (find_string(Paths.paths[i], ".h", 0) != -1)
			{
				//��λ��·��
				normalization_path(Paths.paths[i]);

				std::vector<std::string> StringArray;
				simple_cpp_helper_file::load_file_to_strings(Paths.paths[i], StringArray);

				if (IsCheckAllowCodeReflection(StringArray))
				{
					//�ռ�����
					ClassAnalysis ClassAnalysis;
					vector<string>* PathReflectionCodeCpp = NULL;
					for (auto& Tmp : Modulars)
					{
						//E:\RenZhaiEngine\Source\RenZhaiBuildTool\CodeReflection\xx.j
						if (find_string(Paths.paths[i], Tmp.first.c_str(), 0) != -1)
						{
							ClassAnalysis.ModularPath = Tmp.first;
							PathReflectionCodeCpp = &Tmp.second;
							break;
						}
					}

					CollectClassInfo::Collection(Paths.paths[i], ClassAnalysis);

					//����.h��.cpp����
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

					if (PathReflectionCodeCpp)
					{
						//����·��
						if (1)
						{
							PathReflectionCodeCpp->push_back(
								simple_cpp_string_algorithm::printf(
									"#include \"%s\"", PathCPP.c_str()));
						}
						else //���·��
						{
							PathReflectionCodeCpp->push_back(
								simple_cpp_string_algorithm::printf(
									"#include \"%s.CodeReflection.cpp\"", Buff));
						}
					}
				}
			}
		}

		for (auto& Tmp : Modulars)
		{
			if (Tmp.second.size() > 0)
			{
				string LinkCodeReflection = simple_cpp_string_algorithm::printf(
					"%sLinkCodeReflection.build.cpp", Tmp.first.c_str());

				simple_cpp_helper_file::save_file_to_strings(LinkCodeReflection, Tmp.second);
			}
		}
	return 0;
}