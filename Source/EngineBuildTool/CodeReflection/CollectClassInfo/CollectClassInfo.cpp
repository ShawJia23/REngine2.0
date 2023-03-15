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
	const char EqualSign[] = "=";
	const char Colon[] = "\"";

	//切割CodeType
	void ProcessingVariableReflexParameters(
		const string& InRowStrong,
		VariableAnalysis& InVariableAnalysis)
	{
		char* Ptr = const_cast<char*>(InRowStrong.c_str());

		char R[1024] = { 0 };
		char L[1024] = { 0 };


		split(Ptr, LeftParenthesisString, L, R, false);


		trim_start_and_end_inline(R);

		remove_char_end(R, ')');

		vector<string> ElementStr;
		simple_cpp_string_algorithm::parse_into_vector_array(R, ElementStr, CommaString);

		for (auto& Tmp : ElementStr)
		{
			char* RowPtr = const_cast<char*>(Tmp.c_str());
			if (simple_cpp_string_algorithm::string_contain(Tmp, EqualSign))
			{
				char EqualR[1024] = { 0 };
				char EqualL[1024] = { 0 };

				split(RowPtr, EqualSign, EqualL, EqualR, false);
				trim_start_and_end_inline(EqualL);

				if (simple_cpp_string_algorithm::string_contain(EqualR, Colon))
				{
					remove_all_char_end(EqualR, '\"');
				}
				trim_start_and_end_inline(EqualR);
				InVariableAnalysis.Metas.insert({ EqualL,EqualR });
			}
			else 
			{
				trim_start_and_end_inline(RowPtr);
				InVariableAnalysis.Fields.push_back(RowPtr);
			}
		}
	}

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
		char rStr[1024] = { 0 };
		char lStr[1024] = { 0 };

		char* ptr = const_cast<char*>(rowStrong.c_str());
		split(ptr, CodeType, rStr, lStr, false);

		vector<string> elementStr;
		simple_cpp_string_algorithm::parse_into_vector_array(lStr, elementStr, CommaString);

		if (elementStr[0].find("Resources"))
		{
			variableAnalysis->CodeType = "Resources";
			return true;
		}

		return false;
	}

	void AnalyticParameters(char* LStr, std::vector<ParamElement>& OutParam)
	{
		//解析参数和参数名
		vector<string> ElementStr;
		simple_cpp_string_algorithm::parse_into_vector_array(LStr, ElementStr, CommaString);

		//收集变量
		for (std::string& Ele : ElementStr)
		{
			char* ElePtr = const_cast<char*>(Ele.c_str());

			if (Ele == "")
			{
				continue;
			}

			//移除前后空格
			trim_start_and_end_inline(ElePtr);

			OutParam.push_back(ParamElement());
			ParamElement& paramElement = OutParam[OutParam.size() - 1];

			char R[1024] = { 0 };
			char L[1024] = { 0 };
			if (simple_cpp_string_algorithm::string_contain(Ele, StarString))
			{
				paramElement.bPointer = true;
				split(ElePtr, StarString, R, L, false);
			}
			else if (simple_cpp_string_algorithm::string_contain(Ele, FetchAddressString))
			{
				paramElement.bReference = true;
				split(ElePtr, FetchAddressString, R, L, false);
			}
			else
			{
				split(ElePtr, SpaceString, R, L, false);
				if (R[0] == '\0')
				{
					strcpy(R, ElePtr);
				}
			}

			if (c_str_contain(R, "const"))
			{
				paramElement.bConst = true;

				remove_string_start(R, "const");
			}

			trim_start_and_end_inline(R);
			trim_start_and_end_inline(L);

			paramElement.Type = R;
			paramElement.Name = L;
		}
	}

	bool Collection(const string& paths, ClassAnalysis& classAnalysis)
	{
		std::vector<std::string> stringArray;
		simple_cpp_helper_file::load_file_to_strings(paths, stringArray);

		classAnalysis.CodeHName = paths;

		//遍历每一行代码
		for (int i = 0; i < stringArray.size(); i++)
		{
			string& row = stringArray[i];
			char* rowPtr = const_cast<char*>(row.c_str());

			//包含
			auto contain = [&](const char* inSubString)->bool
			{
				return simple_cpp_string_algorithm::string_contain(row, inSubString);
			};

			if (contain("CODEREFLECTION"))
			{
				classAnalysis.CodeLine = i + 1;
			}

			//获取类名和继承名
			if ((contain("\tclass") || contain("class")) &&
				contain(":") &&
				(contain("protected") || contain("private") || contain("public")))
			{
				remove_string_start(rowPtr, "class ");
				remove_string_start(rowPtr, "\tclass ");

				if (contain("_API"))
				{
					trim_start_inline(rowPtr);

					char R[1024] = { 0 };
					char L[1024] = { 0 };

					split(rowPtr, SpaceString, L, R, false);

					classAnalysis.APIName = L;

					row = R;
				}

				vector<string> elementStr;
				simple_cpp_string_algorithm::parse_into_vector_array(rowPtr, elementStr, ColonString);

				//前后有空格 修剪
				trim_start_and_end_inline(const_cast<char*>(elementStr[0].c_str()));

				classAnalysis.ClassName = elementStr[0];
				classAnalysis.CodeCPPName = elementStr[0];
				//去除前缀
				{
					char* ClearClassNamePtr = const_cast<char*>(classAnalysis.CodeCPPName.c_str());

					trim_start_and_end_inline(ClearClassNamePtr);

					remove_char_start(ClearClassNamePtr, 'R');
					remove_char_start(ClearClassNamePtr, 'G');
				}

				//考虑到多继承问题
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

			//获取标记的成员函数
			if (contain("RFUNCTION"))
			{
				FunctionAnalysis functionAnalysis;
				if (GetCodeTypeByFunc(row, functionAnalysis))
				{
					row = stringArray[i + 1];

					if (contain("\tstatic") || contain("static "))
					{
						functionAnalysis.bStatic = true;

						char L[1024] = { 0 };
						char R[1024] = { 0 };
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

					//确定函数的返回类型
					char Tmp[1024] = { 0 };
					{
						char L[1024] = { 0 };

						split(row.c_str(), SpaceString, L, Tmp, false);

						functionAnalysis.Return = CollectionVariableType(L, ECollectionParmType::Type_Return);

						{
							remove_char_end(Tmp, '}');
							remove_char_end(Tmp, '{');
							trim_end_inline(Tmp);
							remove_char_end(Tmp, ';');
							remove_char_end(Tmp, ')');
						}

						char lStr[1024] = { 0 };
						char rStr[1024] = { 0 };

						split(Tmp, LeftParenthesisString, lStr, rStr, false);

						//函数名
						functionAnalysis.FunctionName = lStr;

						//解析参数和参数名
						vector<string> elementStr;
						simple_cpp_string_algorithm::parse_into_vector_array(rStr, elementStr, CommaString);

						//收集变量
						for (std::string& Ele : elementStr)
						{
							char* ElePtr = const_cast<char*>(Ele.c_str());

							if (Ele == "")
							{
								continue;
							}
							trim_start_and_end_inline(ElePtr);

							ParamElement paramElement;

							char L[1024] = { 0 };
							char R[1024] = { 0 };
							if (simple_cpp_string_algorithm::string_contain(Ele, StarString))
							{
								paramElement.bPointer = true;
								split(ElePtr, StarString, L, R, false);
							}
							else if (simple_cpp_string_algorithm::string_contain(Ele, FetchAddressString))
							{
								paramElement.bReference = true;
								split(ElePtr, FetchAddressString, L, R, false);
							}
							else
							{
								split(ElePtr, SpaceString, L, R, false);
							}

							if (c_str_contain(L, "const"))
							{
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

			////获取标记的成员变量
			if (contain("RVARIABLE"))
			{
				if (contain("CodeType"))
				{
					VariableAnalysis variableAnalysis;
					if (GetCodeTypeByProp(row, &variableAnalysis))
					{
						ProcessingVariableReflexParameters(row, variableAnalysis);

						char R[1024] = { 0 };
						char L[1024] = { 0 };

						row = stringArray[i + 1];

						remove_char_start(rowPtr, '\t');
						remove_char_end(rowPtr, ';');

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

						//是不是模板
						if (c_str_contain(R, "<") && c_str_contain(R, ">"))
						{
							char TempR[1024] = { 0 };
							char TempL[1024] = { 0 };
							split(R, "<", TempR, TempL, false);

							variableAnalysis.Type = TempR;

							remove_char_end(TempL, '>');

							AnalyticParameters(TempL, variableAnalysis.InternalType);
						}
						else
						{
							variableAnalysis.Type = R;
						}
						variableAnalysis.Name = L;

						classAnalysis.Variable.push_back(variableAnalysis);
					}
				}
			}
		}

		return true;
	}
}