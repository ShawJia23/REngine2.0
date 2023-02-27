#pragma once
#include <map>
#include <string>
#include<vector>
class RMinimalObject;
class RFunctionObject;
class RPropertyObject;

struct RNativeClass
{
public:
	RNativeClass();

	void AddProperty(
		const std::string& PropertyName,
		const std::string& InType,
		int InCount,
		int InElementSize,
		void* InData);

	void AddClassType(const std::string& InType);

	RPropertyObject* FindProperty(const std::string& InPropertyString);
public:
	bool IsExitFields(const std::string& InField);
	int FindFields(const std::string& InField);
	std::string* FindMetas(const std::string& InKey);
public:
	void AddMetas(const std::string& InKeyString, const std::string& InValue);
	void AddMetas(const std::string& InPropertyName, const std::string& InKeyString, const std::string& InValue);

	void AddFields(const std::string& InPropertyName, const std::string& InFields);
	void AddFields(const std::string& InFields);

	std::map<std::string, std::string> Metas;
	std::vector<std::string> Fields;
public:
	std::map<std::string, RFunctionObject*> FunctionList;
	
	std::vector<std::string> InheritClassTypes;
	RPropertyObject* Property;
	RMinimalObject* Outer;
};