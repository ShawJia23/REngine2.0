
#include "RFrame.h"
#include "ScriptMacro.h"

RNativeFuntionPtr GScriptNatives[Script_Max];

RFrame::RFrame()
{
}

RFrame::RFrame(RFunctionObject* InNewFunction)
{
}

float RFrame::ReadFloat()
{
	return Read<float>();
}

int RFrame::ReadInt()
{
	return Read<int>();
}

void RFrame::AddParm(RPropertyObject* Addr)
{
	std::shared_ptr<ROutParm> ListParm = OutParm;

	if (!ListParm.get())
	{
		OutParm = std::make_shared<ROutParm>();
		OutParm->PropAddr = Addr;
	}
	else
	{
		while (ListParm->Nest.get())
		{
			ListParm = ListParm->Nest;
		}

		ListParm->Nest = std::make_shared<ROutParm>();
		ListParm->Nest->PropAddr = Addr;
	}
}

void RFrame::Step(RMinimalObject* Context, void const* RefData)
{
	int B = *Code++;
	(GScriptNatives[B])(Context, *this, RefData);
}

unsigned char* RFrame::GetParmAddr()
{
	RPropertyObject* Proper = OutParm->PropAddr;
	OutParm = OutParm->Nest;



	return nullptr;
}

ROutParm::ROutParm()
	:PropAddr(nullptr)
{
}

FUNCTION_IMPLEMENTATION(RMinimalObject::Script_Undefined)
{

}

FUNCTION_IMPLEMENTATION(RMinimalObject::Script_Int)
{
	*(int*)RefData = Stack.ReadInt();
}

FUNCTION_IMPLEMENTATION(RMinimalObject::Script_Float)
{
	*(float*)RefData = Stack.ReadFloat();
}

FUNCTION_IMPLEMENTATION(RMinimalObject::Script_Funtion)
{

}