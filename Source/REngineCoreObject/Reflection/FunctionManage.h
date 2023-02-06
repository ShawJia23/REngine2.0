#pragma once

#include "../RObjectMacro.h"
#include "../RCoreObjectMinimal.h"
#include "../RObject/RMinimalObject.h"
#include "RFrame.h"

class RFunctionObject;

struct RENGINECOREOBJECT_API RFuntionID
{
	std::string ClassName;
	std::string FuncName;

	RNativeFuntionPtr NativeFuncPtr;

	RFuntionID(const std::string& InNewClassName, const std::string& InNewFuncName, RNativeFuntionPtr NewNativeFuncPtr)
		:ClassName(InNewClassName)
		, FuncName(InNewFuncName)
		, NativeFuncPtr(NewNativeFuncPtr)
	{}
};

struct RENGINECOREOBJECT_API RFuntionManage
{
	static RNativeFuntionPtr& GetNativeFuncPtr(RFunctionObject* Function);
	static int SetNativeFuncPtr(const RFuntionID& Function);
private:
	static vector<RFuntionID> FunctionList;
};