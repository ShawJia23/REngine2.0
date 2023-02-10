#include "SpawnIntermediateFile.h"

namespace IntermediateFile
{
	const string* GetInheritName(const std::vector<string>& InheritName)
	{
		for (auto& Tmp : InheritName)
		{
			if (!Tmp.empty())
			{
				if (Tmp.c_str()[0] == 'R' || Tmp.c_str()[0] == 'G')
				{
					return &Tmp;
				}
			}
		}

		return NULL;
	}

	std::string GetCombineParmString(
		const FunctionAnalysis& Function,
		std::vector<std::string>& ParamArray)
	{
		if (Function.ParamArray.size() == 0)
		{
			return "";
		}
		else
		{
			std::string ParamString;
			for (auto& Param : Function.ParamArray)
			{
				//int   c, float   b
				std::string NewParam =
					simple_cpp_string_algorithm::printf(
						"%s %s%s %s",
						string((Param.bConst ? ("const") : (""))).c_str(),
						Param.Type.c_str(),
						string((Param.bPointer ? ("* ") : (Param.bReference ? ("& ") : (" ")))).c_str(),
						Param.Name.c_str());

				//int32 A,
				ParamString += NewParam + (",");

				//int32 A,int32 B.int32 c
				ParamArray.push_back(NewParam);
			}

			remove_char_end(const_cast<char*>(ParamString.c_str()), ',');

			return ParamString;
		}
	}

	void GeneratePointH(
		std::vector<std::string>& AnalysisRaw,
		const ClassAnalysis& ClassAnalysis,
		std::vector<std::string>& StaticRegistration)
	{
		AnalysisRaw.push_back("#pragma once");
		AnalysisRaw.push_back("");

		AnalysisRaw.push_back("#include \"RObject/RMinimalObject.h\"");
		AnalysisRaw.push_back("#include \"Reflection/RFrame.h\"");
		AnalysisRaw.push_back("#include \"Reflection/ScriptMacro.h\"");
		AnalysisRaw.push_back("");

		std::string MClassName =
			simple_cpp_string_algorithm::printf(
				" Z_BT_%s", ClassAnalysis.ClassName.c_str());

		//#define  Z_BT_GActorObject
		AnalysisRaw.push_back(
			simple_cpp_string_algorithm::printf("#define %s %s",
				MClassName.c_str(),
				string((ClassAnalysis.Function.size() > 0) ? "\\" : "").c_str()));

		AnalysisRaw.push_back("public: \\");
		//����
		std::string ClearClassName = ClassAnalysis.ClassName;
		{
			char* ClearClassNamePtr = const_cast<char*>(ClearClassName.c_str());
			trim_start_and_end_inline(ClearClassNamePtr);

			//�Ƴ�ͷ�� 
			remove_char_start(ClearClassNamePtr, 'R');
			remove_char_start(ClearClassNamePtr, 'G');
		}

		if (ClassAnalysis.Function.size() > 0)
		{
			for (const FunctionAnalysis& Function : ClassAnalysis.Function)
			{
				if (Function.CodeType == "Function" ||
					Function.CodeType == "PureFunction")
				{
					//Script_Hello1
					std::string VMString =
						simple_cpp_string_algorithm::printf(
							"Script_%s",
							Function.FunctionName.c_str());

					//FUNCTION_DEFINITION(Script_Hello1) 
					AnalysisRaw.push_back(
						simple_cpp_string_algorithm::printf("FUNCTION_DEFINITION(%s) \\", VMString.c_str()));

					AnalysisRaw.push_back("{ \\");
					{
						//a,b,c,d
						std::string VariableAdd;
						//��ƴ�Ӻ����Ĳ���
						for (const ParamElement& Variable : Function.ParamArray)
						{
							std::string StackString = " Stack.GetParmAddr(); \\";

							std::string VariableName =
								simple_cpp_string_algorithm::printf(
									" Z_%s_Name",
									Variable.Name.c_str());

							//float Z_a = *(float*)Stack.GetParmAddr();
							AnalysisRaw.push_back(
								simple_cpp_string_algorithm::printf(
									"\t%s%s %s = %s(%s*)%s",
									Variable.Type.c_str(),
									string(Variable.bPointer ? "*" : "").c_str(),
									VariableName.c_str(),
									std::string(Variable.bPointer ? "" : "*").c_str(),
									Variable.Type.c_str(),
									StackString.c_str()));

							//,Z_Context_Name, Z_A_Name, Z_b_Name, Z_C_Name
							VariableAdd += ("," + VariableName);
						}
						//�Ƴ���ǰ����ַ���
						char* VariableAddPtr = const_cast<char*>(VariableAdd.c_str());
						remove_char_start(VariableAddPtr, ',');

						//������
						if (Function.bStatic)
						{
							if (Function.Return.Type == "void")
							{
								//GActorObject::Hello1(Z_a,Z_b); 
								AnalysisRaw.push_back(
									simple_cpp_string_algorithm::printf(
										"\t%s::%s(%s); \\",
										ClassAnalysis.ClassName.c_str(),
										Function.FunctionName.c_str(),
										VariableAdd.c_str()));
							}
							else
							{
								/**(std::string*)RefData = GActorObject::Hello3( Z_Context_Name); \*/
								AnalysisRaw.push_back(
									simple_cpp_string_algorithm::printf(
										"\t%s(%s*) RefData = %s::%s(%s); \\",
										string(Function.Return.bPointer ? "" : "*").c_str(),
										Function.Return.Type.c_str(),
										ClassAnalysis.ClassName.c_str(),
										Function.FunctionName.c_str(),
										VariableAdd.c_str()));
							}
						}
						else //�����Ա����
						{

						}
					}
					AnalysisRaw.push_back("} \\");

					//�ռ���̬ע��
					//FFuntionManage::SetNativeFuncPtr(FFuntionID(("ActorObject"),("Hello1"),GActorObject::Script_Hello1));
					StaticRegistration.push_back(
						simple_cpp_string_algorithm::printf(
							"\tFFuntionManage::SetNativeFuncPtr(FFuntionID((\"%s\"),(\"%s\"),%s::%s));",
							ClearClassName.c_str(),
							Function.FunctionName.c_str(),
							ClassAnalysis.ClassName.c_str(),
							VMString.c_str()));
				}
			}

		}
		AnalysisRaw.push_back("private:");

		AnalysisRaw.push_back((""));

		//�ϲ��ڲ��ĺ���
	//GActorObject_10_Internal_Fun
		std::string InternalFunMacro = simple_cpp_string_algorithm::printf(
			"%s_%i_Internal_Fun",
			ClassAnalysis.ClassName.c_str(),
			ClassAnalysis.CodeLine);

		//#define GActorObject_10_Internal_Fun 
		AnalysisRaw.push_back(
			simple_cpp_string_algorithm::printf(
				"#define %s \\",
				InternalFunMacro.c_str()));

		if (const string* InheritName = GetInheritName(ClassAnalysis.InheritName))
		{
			AnalysisRaw.push_back(
				simple_cpp_string_algorithm::printf(
					"typedef %s Super; \\",
					InheritName->c_str()));
		}
		AnalysisRaw.push_back("protected: \\");
		AnalysisRaw.push_back("virtual void InitReflectionContent(); \\");
		AnalysisRaw.push_back("private:");

		AnalysisRaw.push_back("");

		AnalysisRaw.push_back(
			simple_cpp_string_algorithm::printf(
				"#define %s_%i_GENERATED_BODY_BT \\",
				ClassAnalysis.ClassName.c_str(),
				ClassAnalysis.CodeLine));

		// Z_BT_GActorObject
		AnalysisRaw.push_back(simple_cpp_string_algorithm::printf(
			"%s \\", MClassName.c_str()));
		AnalysisRaw.push_back(simple_cpp_string_algorithm::printf(
			"%s ", InternalFunMacro.c_str()));

		AnalysisRaw.push_back((""));

		AnalysisRaw.push_back("#ifdef CURRENT_FILE_ID_BT");
		AnalysisRaw.push_back("#undef CURRENT_FILE_ID_BT");
		AnalysisRaw.push_back("#endif // CURRENT_FILE_ID_BT");

		AnalysisRaw.push_back("");

		AnalysisRaw.push_back("#ifdef CodeReflectionTagLine");
		AnalysisRaw.push_back("#undef CodeReflectionTagLine");
		AnalysisRaw.push_back("#endif // NewLine");

		AnalysisRaw.push_back("");

		//#define CURRENT_FILE_ID_BT  GActorObject
		AnalysisRaw.push_back(
			simple_cpp_string_algorithm::printf(
				"#define %s %s",
				std::string("CURRENT_FILE_ID_BT ").c_str(),
				ClassAnalysis.ClassName.c_str()));

		//#define NewLine 10
		AnalysisRaw.push_back(
			simple_cpp_string_algorithm::printf(
				"#define %s %i",
				std::string("NewLine").c_str(),
				ClassAnalysis.CodeLine));
	}

	void GeneratePointCpp(
		std::vector<std::string>& AnalysisRaw,
		const ClassAnalysis& ClassAnalysis,
		std::vector<std::string>& StaticRegistration)
	{
		AnalysisRaw.push_back("/*===========================================================================");
		AnalysisRaw.push_back("	Generated code exported from c f.");
		AnalysisRaw.push_back("===========================================================================*/");

		//�ļ��ľ���·��
		AnalysisRaw.push_back(simple_cpp_string_algorithm::printf(
			"#include \"%s\"",
			ClassAnalysis.CodeHName.c_str()));

		////�����.h
		//AnalysisRaw.push_back(simple_cpp_string_algorithm::printf(
		//	"#include \"%s.CodeReflection.h\"",
		//	ClassAnalysis.CodeCPPName.c_str()));

		AnalysisRaw.push_back("#include \"Reflection/FunctionManage.h\"");

		AnalysisRaw.push_back("");
		AnalysisRaw.push_back("#ifdef _MSC_VER");
		AnalysisRaw.push_back("#pragma warning (push)");
		AnalysisRaw.push_back("#pragma warning (disable : 4883)");
		AnalysisRaw.push_back("#endif");
		AnalysisRaw.push_back("PRAGMA_DISABLE_DEPRECATION_WARNINGS");
		AnalysisRaw.push_back("");
		//���붨����
		{
			//������
			if (ClassAnalysis.Function.size() > 0)
			{
				for (const FunctionAnalysis& Function : ClassAnalysis.Function)
				{
					if (Function.CodeType == "Event")
					{
						//Name_Hello123
						std::string FunctionName =
							simple_cpp_string_algorithm::printf("Name_%s",
								Function.FunctionName.c_str());

						std::vector<std::string> ParamStr;
						//static std::string Name_Hello123 = std::string(("Hello123"));v
						AnalysisRaw.push_back(
							simple_cpp_string_algorithm::printf(
								"static std::string %s = std::string((\"%s\"));",
								FunctionName.c_str(),
								Function.FunctionName.c_str()
							));

						//void   ActorObject::Hello123( int   c, float   b)
						AnalysisRaw.push_back(
							simple_cpp_string_algorithm::printf(
								"%s %s %s::%s(%s)",
								Function.Return.Type.c_str(),
								string((Function.Return.bPointer ? ("*") : (Function.Return.bReference ? ("&") : (" ")))).c_str(),
								ClassAnalysis.ClassName.c_str(),
								Function.FunctionName.c_str(),
								GetCombineParmString(Function, ParamStr).c_str()
							));

						AnalysisRaw.push_back(("{"));
						{
							//Parm_Hello123
							std::string StructName =
								simple_cpp_string_algorithm::printf(
									"Parm_%s",
									Function.FunctionName.c_str());

							if (Function.ParamArray.size() > 0)
							{
								//struct FParm_Hello123
								AnalysisRaw.push_back(
									simple_cpp_string_algorithm::printf("\tstruct F%s",
										StructName.c_str()));
								AnalysisRaw.push_back(std::string(("\t{")));//{
								{
									for (auto& Param : ParamStr)
									{
										AnalysisRaw.push_back(
											simple_cpp_string_algorithm::printf("\t\t%s;",
												Param.c_str()));
									}
								}
								AnalysisRaw.push_back(std::string(("\t};")));//};

								//FParm_Hello123 Parm_Hello123;
								AnalysisRaw.push_back(
									simple_cpp_string_algorithm::printf(
										"\tF%s %s;",
										StructName.c_str(),
										StructName.c_str()));

								//��ֵ
								{
									//Parm_Hello123.c = c;
									for (auto& Param : Function.ParamArray)
									{
										AnalysisRaw.push_back(
											simple_cpp_string_algorithm::printf(
												"\t%s.%s = %s;",
												StructName.c_str(),
												Param.Name.c_str(),
												Param.Name.c_str()));
									}
								}
							}

							//ExecutionScript(FindScriptFuntion(Name_Hello123), &Parm_Hello123);
							AnalysisRaw.push_back(
								simple_cpp_string_algorithm::printf(
									"\tExecutionScript(FindScriptFuntion(%s),%s);",
									FunctionName.c_str(),
									string(Function.ParamArray.size() == 0 ? ("NULL") : (("&") + StructName)).c_str()
								));
						}
						AnalysisRaw.push_back(("} "));
					}
				}
			}

			AnalysisRaw.push_back((""));

			AnalysisRaw.push_back(
				simple_cpp_string_algorithm::printf(
					"void %s::InitReflectionContent()",
					ClassAnalysis.ClassName.c_str()));
			AnalysisRaw.push_back("{");
			{
				//Rename("ActorObject");
				AnalysisRaw.push_back(
					simple_cpp_string_algorithm::printf(
						"\tRename(\"%s\");",
						ClassAnalysis.CodeCPPName.c_str()));
			}

			AnalysisRaw.push_back("}");

			AnalysisRaw.push_back((""));

			AnalysisRaw.push_back(("/* 1xxxx xxxx "));
			AnalysisRaw.push_back((" 2xxxx xxxx */"));
			//Register_ActorObject
			std::string Register_Func =
				simple_cpp_string_algorithm::printf("Register_%s()",
					ClassAnalysis.ClassName.c_str());
			//int Register_ActorObject()
			AnalysisRaw.push_back(
				simple_cpp_string_algorithm::printf("int %s", Register_Func.c_str()));
			AnalysisRaw.push_back(("{"));
			{
				//�ϲ�����vector
				AnalysisRaw.insert(
					AnalysisRaw.end(),
					StaticRegistration.begin(),
					StaticRegistration.end());

				AnalysisRaw.push_back((""));
				AnalysisRaw.push_back(("\treturn 0;"));
			}
			AnalysisRaw.push_back(("}"));

			//static int ActorObject_Index = Register_ActorObject();
			AnalysisRaw.push_back(
				simple_cpp_string_algorithm::printf(
					"static int %s_Index = %s;",
					ClassAnalysis.ClassName.c_str(),
					Register_Func.c_str()));
		}

		AnalysisRaw.push_back("");

		AnalysisRaw.push_back("#ifdef _MSC_VER");
		AnalysisRaw.push_back("#pragma warning (pop)");
		AnalysisRaw.push_back("#endif");
	}

	bool Builder(
		const ClassAnalysis& InClassAnalysis,
		std::vector<std::string>& OutAnalysisRawH,
		std::vector<std::string>& OutAnalysisRawCPP)
	{
		vector<string> StaticRegistration;

		//���ɷ�������
		GeneratePointH(OutAnalysisRawH, InClassAnalysis, StaticRegistration);
		GeneratePointCpp(OutAnalysisRawCPP, InClassAnalysis, StaticRegistration);

		return OutAnalysisRawH.size() && OutAnalysisRawH.size();
	}
}

/*
* .h���ɵĴ���
#pragma once

#include "CoreObject/CoreMinimalObject.h"
#include "CodeReflection/Frame.h"
#include "CodeReflection/ScriptMacro.h"

#define  Z_BT_GActorObject \
FUNCTION_DEFINITION(Script_Hello1) \
{ \
	float Z_a = *(float*)Stack.GetParmAddr();\
	float Z_b = *(float*)Stack.GetParmAddr();\
	GActorObject::Hello1(Z_a,Z_b); \
} \
FUNCTION_DEFINITION(Script_Hello2) \
{ \
	GActorObject::Hello2(); \
}

#define GActorObject_10_GENERATED_BODY_BT \
 Z_BT_GActorObject

#define CURRENT_FILE_ID_BT  GActorObject
#define NewLine 10
*/