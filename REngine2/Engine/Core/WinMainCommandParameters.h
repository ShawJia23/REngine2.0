﻿#pragma once

#if defined(_WIN32)
#include "../EngineMinimal.h"
class WinMainCommandParameters
{
public:
	WinMainCommandParameters(HINSTANCE InhInstance, HINSTANCE InprevInstance, PSTR IncmdLine, int InshowCmd);

	HINSTANCE HInstance;
	HINSTANCE PrevInstance;
	PSTR CmdLine;
	int ShowCmd;
};

#elif 0

#endif // 0

