#include "FunctionManage.h"
#include "../RObject/FunctionObject.h"

vector<RFuntionID> RFuntionManage::FunctionList;

namespace NativeFuntionMess
{
	void Error(RMinimalObject* Context, RFrame& TheStack, void const* RefData)
	{
		assert(0);
	}

	void Empty(RMinimalObject* Context, RFrame& TheStack, void const* RefData)
	{
	}
}

RNativeFuntionPtr ErrorFunction = NativeFuntionMess::Error;
RNativeFuntionPtr EmptyFunction = NativeFuntionMess::Empty;

RNativeFuntionPtr& RFuntionManage::GetNativeFuncPtr(RFunctionObject* Function)
{
	for (auto& Func : FunctionList)
	{
		if (Function->GetName() == Func.FuncName && //函数名
			Function->GetOuter()->GetName() == Func.ClassName) //类名
		{
			return Func.NativeFuncPtr;
		}
	}

	return EmptyFunction;
}

int RFuntionManage::SetNativeFuncPtr(const RFuntionID& Function)
{
	FunctionList.push_back(Function);

	return 0;
}
