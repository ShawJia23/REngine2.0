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
public:
	std::map<std::string, RFunctionObject*> FunctionList;
	std::map<std::string, std::string> Metas;
	std::vector<std::string> InheritClassTypes;
	RPropertyObject* Property;
	RMinimalObject* Outer;
};