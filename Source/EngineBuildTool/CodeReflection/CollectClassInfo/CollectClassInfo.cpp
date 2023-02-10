#include"CollectClassInfo.h"

namespace CollectClassInfo 
{
	const char SpaceString[] = " ";
	const char ColonString[] = ":";
	const char CommaString[] = ",";
	const char LeftParenthesisString[] = "(";
	const char StarString[] = "*";
	const char FetchAddressString[] = "&";
	const char CodeType[] = "CodeType";

	bool GetCodeTypeByFunc(
		const string& rowStrong,
		FunctionAnalysis& functionAnalysis)
	{
		char* ptr = const_cast<char*>(rowStrong.c_str());

		char rStr[1024] = { 0 };
		char lStr[1024] = { 0 };

		split(ptr, CodeType, lStr, rStr, false);

		if (simple_cpp_string_algorithm::string_contain(rStr, "Event"))
		{
			functionAnalysis.CodeType = "Event";

			return true;
		}
		else if (simple_cpp_string_algorithm::string_contain(rStr, "Function"))
		{
			functionAnalysis.CodeType = "Function";

			return true;
		}
		else if (simple_cpp_string_algorithm::string_contain(rStr, "PureFunction"))
		{
			functionAnalysis.CodeType = "PureFunction";

			return true;
		}

		return false;
	}

	ParamElement CollectionVariableType(
		std::string variable,
		ECollectionParmType collectionParmType = ECollectionParmType::Type_Parm)
	{
		char* ptr = const_cast<char*>(variable.c_str());

		//& 
		ParamElement paramElement;
		paramElement.Name = "ReturnValue";

		if (simple_cpp_string_algorithm::string_contain(variable, StarString))
		{
			remove_char_end(ptr, '*');
			paramElement.bPointer = true;
		}

		if (simple_cpp_string_algorithm::string_contain(variable, FetchAddressString))
		{
			remove_char_end(ptr, '&');
			paramElement.bReference = true;
		}

		//int  
		if (simple_cpp_string_algorithm::string_contain(variable, "const"))
		{
			trim_start_and_end_inline(ptr);

			remove_string_start(ptr, "const");
			paramElement.bConst = true;
		}

		trim_start_and_end_inline(ptr);

		remove_char_start(const_cast<char*>(variable.c_str()), '\t');
		paramElement.Type = variable;

		return paramElement;
	}

	bool GetCodeTypeByProp(
		const string& rowStrong,
		VariableAnalysis* variableAnalysis)
	{
		//RowStrong = UPROPERTY(Meta = (CodeType = "Resources", Group = "SimpleCodeLibrary"))

		char rStr[1024] = { 0 };
		char lStr[1024] = { 0 };

		char* ptr = const_cast<char*>(rowStrong.c_str());
		split(ptr, CodeType, rStr, lStr, false);

		//R =  UPROPERTY(Meta = (
		//L =  = "Resources", Group = "SimpleCodeLibrary"))

		vector<string> elementStr;
		simple_cpp_string_algorithm::parse_into_vector_array(lStr, elementStr, CommaString);

		// "Resources" 0 
		// Group = "SimpleCodeLibrary")) 1
		if (elementStr[0].find("Resources"))
		{
			variableAnalysis->CodeType = "Resources";
			return true;
		}

		return false;
	}

	bool Collection(const string& paths, ClassAnalysis& classAnalysis)
	{
		std::vector<std::string> stringArray;
		simple_cpp_helper_file::load_file_to_strings(paths, stringArray);

		classAnalysis.CodeHName = paths;

		//����ÿһ�д���
		for (int i = 0; i < stringArray.size(); i++)
		{
			string& row = stringArray[i];
			char* rowPtr = const_cast<char*>(row.c_str());

			//����
			auto contain = [&](const char* inSubString)->bool
			{
				return simple_cpp_string_algorithm::string_contain(row, inSubString);
			};

			if (contain("CODEREFLECTION"))
			{
				classAnalysis.CodeLine = i + 1;
			}

			//��ȡ�����ͼ̳���
			if ((contain("\tclass") || contain("class")) &&
				contain(":") &&
				(contain("protected") || contain("private") || contain("public")))
			{
				//class FRenderingPipeline :public IDirectXDeviceInterfece
				//FRenderingPipeline :public IDirectXDeviceInterfece
				remove_string_start(rowPtr, "class ");
				remove_string_start(rowPtr, "\tclass ");

				if (contain("_API"))
				{
					//XXX_API FRenderingPipeline :public IDirectXDeviceInterfece
					//L ="XXX_API" R = " FRenderingPipeline :public IDirectXDeviceInterfece"
					trim_start_inline(rowPtr);

					char R[1024] = { 0 };
					char L[1024] = { 0 };

					split(rowPtr, SpaceString, L, R, false);

					//API����
					classAnalysis.APIName = L;

					row = R;
				}

				vector<string> elementStr;
				simple_cpp_string_algorithm::parse_into_vector_array(rowPtr, elementStr, ColonString);

				//���ǰ���пո� �Ͱ����޼���
				trim_start_and_end_inline(const_cast<char*>(elementStr[0].c_str()));

				classAnalysis.ClassName = elementStr[0];
				classAnalysis.CodeCPPName = elementStr[0];
				//ȥ��ǰ׺
				{
					char* ClearClassNamePtr = const_cast<char*>(classAnalysis.CodeCPPName.c_str());

					trim_start_and_end_inline(ClearClassNamePtr);

					remove_char_start(ClearClassNamePtr, 'R');
					remove_char_start(ClearClassNamePtr, 'G');
				}

				//���ǵ���̳�����
				//public GObject ,public Interxx
				if (elementStr.size() >= 2)
				{
					vector<std::string> inheritElement;

					simple_cpp_string_algorithm::parse_into_vector_array(
						elementStr[1].c_str(), inheritElement, CommaString);

					for (auto& Tmp : inheritElement)
					{
						char* TmpPtr = const_cast<char*>(Tmp.c_str());
						trim_start_inline(TmpPtr);

						remove_string_start(TmpPtr, "public");
						remove_string_start(TmpPtr, "protected");
						remove_string_start(TmpPtr, "private");

						trim_start_inline(TmpPtr);

						classAnalysis.InheritName.push_back(Tmp);
					}
				}
			}

			//��ȡ��ǵĳ�Ա����
			if (contain("RFUNCTION"))
			{
				FunctionAnalysis functionAnalysis;
				if (GetCodeTypeByFunc(row, functionAnalysis))
				{
					row = stringArray[i + 1];
					//static void Hello1(GObject *Context, int32 &A,float b,bool C);

					if (contain("\tstatic") || contain("static "))
					{
						functionAnalysis.bStatic = true;

						char L[1024] = { 0 };
						char R[1024] = { 0 };
						//remove_string_start();
						split(row.c_str(), SpaceString, L, R, false);

						row = R;
					}
					else if (contain("virtual "))
					{
						functionAnalysis.bVirtual = true;

						char L[1024] = { 0 };
						char R[1024] = { 0 };

						split(row.c_str(), SpaceString, L, R, false);

						row = R;
					}

					//ȷ�����Ǻ����ķ�������
					char Tmp[1024] = { 0 };
					{
						//Row =  void Hello1(GObject *Context, int32 &A,float b,bool C);

						char L[1024] = { 0 };
						//trim_start_inline(row.c_str());

						split(row.c_str(), SpaceString, L, Tmp, false);

						////Tmp = Hello1(UObject *Context, int32 &A,float b,bool C);  {}
						functionAnalysis.Return = CollectionVariableType(L, ECollectionParmType::Type_Return);

						{
							//void Hello1(UObject *Context, int32 &A,float b,bool C
							remove_char_end(Tmp, '}');
							remove_char_end(Tmp, '{');
							trim_end_inline(Tmp);
							remove_char_end(Tmp, ';');
							remove_char_end(Tmp, ')');
							//Tmp = Hello1(UObject *Context, int32 &A,float b,bool C
						}

						char lStr[1024] = { 0 };
						char rStr[1024] = { 0 };

						split(Tmp, LeftParenthesisString, lStr, rStr, false);

						//������
						functionAnalysis.FunctionName = lStr;

						//���������Ͳ�����
						vector<string> elementStr;
						simple_cpp_string_algorithm::parse_into_vector_array(rStr, elementStr, CommaString);

						//UObject *Context
						//int32 &A
						//float b
						//bool C

						//�ռ�����
						for (std::string& Ele : elementStr)
						{
							char* ElePtr = const_cast<char*>(Ele.c_str());

							if (Ele == "")
							{
								continue;
							}
							//int32 &A
							//�Ƴ�ǰ��ո�
							trim_start_and_end_inline(ElePtr);

							ParamElement paramElement;

							char L[1024] = { 0 };
							char R[1024] = { 0 };
							if (simple_cpp_string_algorithm::string_contain(Ele, StarString))
							{
								paramElement.bPointer = true;
								//GObject *Context
								split(ElePtr, StarString, L, R, false);
								//R = GObject
								//L = Context
							}
							else if (simple_cpp_string_algorithm::string_contain(Ele, FetchAddressString))
							{
								paramElement.bReference = true;
								split(ElePtr, FetchAddressString, L, R, false);
							}
							else
							{
								//  int a
								split(ElePtr, SpaceString, L, R, false);
							}

							if (c_str_contain(L, "const"))
							{
								//const GObject *Context
								paramElement.bConst = true;

								remove_string_start(L, "const");
							}

							trim_start_and_end_inline(L);
							trim_start_and_end_inline(R);

							paramElement.Type = L;
							paramElement.Name = R;

							functionAnalysis.ParamArray.push_back(paramElement);
						}

						classAnalysis.Function.push_back(functionAnalysis);
					}
				}
			}

			////��ȡ��ǵĳ�Ա����
			if (contain("RVARIABLE"))
			{
				if (contain("CodeType"))
				{
					VariableAnalysis variableAnalysis;
					if (GetCodeTypeByProp(row, &variableAnalysis))
					{
						char R[1024] = { 0 };
						char L[1024] = { 0 };

						row = stringArray[i + 1];

						//Row = \tTSubclassOf<UStaticMesh> Mesh;
						remove_char_start(rowPtr, '\t');
						remove_char_end(rowPtr, ';');

						//Row = TSubclassOf<UStaticMesh> Mesh
						if (contain(StarString))
						{
							variableAnalysis.bPointer = true;
							split(rowPtr, StarString, R, L, false);
						}

						if (contain(FetchAddressString))
						{
							variableAnalysis.bReference = true;
							split(rowPtr, FetchAddressString, R, L, false);
						}

						if (contain(SpaceString))
						{
							split(rowPtr, SpaceString, R, L, false);
						}

						if (c_str_contain(R, "const"))
						{
							variableAnalysis.bConst = true;
							remove_string_start(R, "const");
						}

						trim_start_and_end_inline(R);
						trim_start_and_end_inline(L);

						variableAnalysis.Type = R;
						variableAnalysis.Name = L;

						classAnalysis.Variable.push_back(variableAnalysis);
					}
				}
			}
		}

		return true;
	}
}