#pragma once
#include"GuidInterface.h"
#include"../Reflection/CodeReflection.h"
#include"../Construction/ObjectConstruction.h"
#include"../Reflection/ScriptCommand.h"
#include"../Reflection/ScriptMacro.h"
#include"../Reflection/RNativeClass.h"

class RFrame;
class RFunctionObject;
class RENGINECOREOBJECT_API RMinimalObject :public IGuidInterface
{
public:
	RMinimalObject();
	virtual ~RMinimalObject();
	virtual void InitMinimalObject();
	virtual void InitReflectionContent() {};
	virtual void Init() {};
	virtual void Tick(float DeltaTime) {};

	bool IsTick() { return bTick; }
	void SetTick(bool tick) { bTick=tick; }

	FORCEINLINE RMinimalObject* GetOuter() const { return Outer; }
	FORCEINLINE std::string GetName() const { return m_Name; }
	void SetOuter(RMinimalObject* InNewOuter) { Outer = InNewOuter; }
	void Rename(const std::string& name) { m_Name = name; }

public:
	FUNCTION_DEFINITION(Script_Undefined);
	FUNCTION_DEFINITION(Script_Int);
	FUNCTION_DEFINITION(Script_Float);
	FUNCTION_DEFINITION(Script_Funtion);

public:
	static void CallFunction(RFrame& Stack, void const* Data, RFunctionObject* Function);
	static void ExecutionScript(RFunctionObject* Function, void const* Data);

	//该函数可以获取编译后带字节码的函数
	RFunctionObject* FindScriptFuntion(const std::string& FunName);
	static RFunctionObject* FindScriptStaticFuntion(const std::string& FunName);
	RNativeClass& GetNativeClass() { return NativeClass; }
protected:
	bool bTick;
	RMinimalObject* Outer;
	std::string m_Name;
	RNativeClass NativeClass;
private:
	std::map<std::string, RFunctionObject*> FunctionList;
};


extern vector<RMinimalObject*> GRObjects;