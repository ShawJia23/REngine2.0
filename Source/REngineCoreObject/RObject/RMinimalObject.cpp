#include"RMinimalObject.h"
#include"../Reflection/RFrame.h"
#include"FunctionObject.h"
#include"PropertyObject.h"
vector<RMinimalObject*>GRObjects;

RMinimalObject::RMinimalObject() 
{
	bTick = true;
	GRObjects.push_back(this);
}
RMinimalObject::~RMinimalObject() 
{
	for (vector<RMinimalObject*>::const_iterator Iter = GRObjects.begin();
		Iter != GRObjects.end();
		++Iter)
	{
		if (*Iter == this)
		{
			GRObjects.erase(Iter);
			break;
		}
	}
}

void RMinimalObject::CallFunction(RFrame& Stack, void const* Data, RFunctionObject* Function)
{
	//收集函数的参数
	RPropertyObject* PropertyPtr = Function->Property;
	while (PropertyPtr)
	{
		Stack.AddParm(PropertyPtr);
		PropertyPtr = dynamic_cast<RPropertyObject*>(PropertyPtr->Nest);
	}

	//空


	//执行字节码对应的命令
	Stack.Step(NULL, Data);
}

void RMinimalObject::ExecutionScript(RFunctionObject* Function, void const* Data)
{
	assert(Function);

	if (Function->Script.size() == 0)
	{
		return;
	}

	RFrame Stack(Function);

	RMinimalObject::CallFunction(Stack, Data, Function);
}

RFunctionObject* RMinimalObject::FindScriptFuntion(const std::string& FunName)
{
	RFunctionObject* NewFuntion = nullptr;
	auto It = FunctionList.find(FunName);
	if (It != FunctionList.end())
	{
		NewFuntion = It->second;
	}

	return NewFuntion;
}

RFunctionObject* RMinimalObject::FindScriptStaticFuntion(const std::string& FunName)
{
	return nullptr;
}

void RMinimalObject::InitMinimalObject()
{
	NativeClass.Outer = this;

	InitReflectionContent();
}
