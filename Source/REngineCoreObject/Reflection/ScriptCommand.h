#pragma once
#include "../RCoreObjectMinimal.h"

//�ֽ����
enum EScriptCommand
{
	Script_Undefined = 0x0B,//Ĭ�ϵ�
	Script_Int = 0x1D,//int
	Script_Float = 0x1D,//float
	Script_Funtion = 0x77,//���к���

	Script_Max = 0x100
};