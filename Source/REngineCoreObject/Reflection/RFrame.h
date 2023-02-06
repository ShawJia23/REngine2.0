#pragma once

#include "../RObjectMacro.h"
#include "../RCoreObjectMinimal.h"
#include "../RObject/RMinimalObject.h"

class RFunctionObject;
class RPropertyObject;

class ROutParm :public std::enable_shared_from_this<ROutParm>
{
public:
	ROutParm();

	RPropertyObject* PropAddr;
	std::shared_ptr<ROutParm> Nest;
};

struct RFrame
{
	RFrame();
	RFrame(RFunctionObject* InNewFunction);

	template<typename Type>
	Type Read();

	float ReadFloat();
	int ReadInt();

	void AddParm(RPropertyObject* Addr);

	void Step(RMinimalObject* Context, void const* RefData);

	RENGINECOREOBJECT_API unsigned char* GetParmAddr();
public:
	unsigned char* Code;
	RFunctionObject* Function;
	std::shared_ptr<ROutParm> OutParm;//Á´±í
};

typedef void(*RNativeFuntionPtr)(RMinimalObject* Context, RFrame& TheStack, void const* RefData);

template<typename Type>
inline Type RFrame::Read()
{
	Type Result = 0;
	int TypeLen = sizeof(Type);

	memcpy(&Result, Code, TypeLen);

	Code += TypeLen;

	return Result;
}
