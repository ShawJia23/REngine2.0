#pragma once
#pragma comment(lib, "SimpleLibrary.lib")
#include "simple_library/public/simple_library.h"
//����
struct ParamElement
{
	string Name; //��������
	bool bConst;//�Ƿ���const
	bool bPointer;//�Ƿ���ָ��*
	bool bReference;//�Ƿ�������&
	string Type;//float int ...

	//�п������ڲ����� ���Ϳ�����ģ��
	vector<struct ParamElement> InternalType;//����ģ�� vector<float> or vector123<float,int,float>...

	std::map<string, string> Metas;
	std::vector<string> Fields;

	ParamElement()
		: bPointer(false)
		, bReference(false)
		, bConst(false)
	{}
};

//����
struct VariableAnalysis :public ParamElement
{
	string CodeType;
	bool bStatic; //�Ƿ��Ǿ�̬

	VariableAnalysis()
		:bStatic(false)
	{}
};

//��������
struct FunctionAnalysis
{
	std::vector<ParamElement> ParamArray;//�����ľ�ֵ̬
	ParamElement Return;//��������

	string FunctionName;//��������
	bool bStatic;//��̬
	bool bVirtual;//����

	string CodeType;//��������

	FunctionAnalysis()
		:bStatic(false)
		, bVirtual(false)
	{}
};

//�������Ա
struct ClassAnalysis
{
	std::vector<FunctionAnalysis> Function;//����
	std::vector<VariableAnalysis> Variable;//���ٱ���

	string APIName;//_API������
	string ClassName;//������

	std::vector<string> InheritName;//�̳�������

	string CodeCPPName;//CPP����
	string CodeHName;//.h�ļ�·��
	int CodeLine;//�������������

	string ModularPath;
};

enum ECollectionParmType
{
	Type_Return,//�Ƿ���
	Type_Parm,//����
};

bool IsCheckAllowCodeReflection(const std::vector<std::string>& InContent);