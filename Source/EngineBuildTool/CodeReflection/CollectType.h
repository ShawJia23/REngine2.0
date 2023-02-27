#pragma once
#pragma comment(lib, "SimpleLibrary.lib")
#include "simple_library/public/simple_library.h"
//参数
struct ParamElement
{
	string Name; //参数名字
	bool bConst;//是否是const
	bool bPointer;//是否是指针*
	bool bReference;//是否是引用&
	string Type;//float int ...

	//有可能是内部类型 类型可能是模板
	vector<struct ParamElement> InternalType;//类似模板 vector<float> or vector123<float,int,float>...

	std::map<string, string> Metas;
	std::vector<string> Fields;

	ParamElement()
		: bPointer(false)
		, bReference(false)
		, bConst(false)
	{}
};

//变量
struct VariableAnalysis :public ParamElement
{
	string CodeType;
	bool bStatic; //是否是静态

	VariableAnalysis()
		:bStatic(false)
	{}
};

//函数解析
struct FunctionAnalysis
{
	std::vector<ParamElement> ParamArray;//函数的静态值
	ParamElement Return;//返回类型

	string FunctionName;//函数名字
	bool bStatic;//静态
	bool bVirtual;//虚拟

	string CodeType;//代码类型

	FunctionAnalysis()
		:bStatic(false)
		, bVirtual(false)
	{}
};

//类解析成员
struct ClassAnalysis
{
	std::vector<FunctionAnalysis> Function;//函数
	std::vector<VariableAnalysis> Variable;//多少变量

	string APIName;//_API的名称
	string ClassName;//类名称

	std::vector<string> InheritName;//继承者名字

	string CodeCPPName;//CPP名字
	string CodeHName;//.h文件路径
	int CodeLine;//反射宏标记在哪行

	string ModularPath;
};

enum ECollectionParmType
{
	Type_Return,//是返回
	Type_Parm,//参数
};

bool IsCheckAllowCodeReflection(const std::vector<std::string>& InContent);