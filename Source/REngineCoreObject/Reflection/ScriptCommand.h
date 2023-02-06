#pragma once
#include "../RCoreObjectMinimal.h"

//字节码表
enum EScriptCommand
{
	Script_Undefined = 0x0B,//默认的
	Script_Int = 0x1D,//int
	Script_Float = 0x1D,//float
	Script_Funtion = 0x77,//呼叫函数

	Script_Max = 0x100
};