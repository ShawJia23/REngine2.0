﻿#pragma once

#if defined(_WIN32)
#include "WinMainCommandParameters.h"
#endif // 1

class REngine
{
public:

	virtual int PreInit(
#if defined(_WIN32)
		WinMainCommandParameters InParameters
#endif // 1
	) = 0;

	virtual int Init(
#if defined(_WIN32)
		WinMainCommandParameters InParameters
#endif // 1
	) = 0;

	virtual int PostInit() = 0;

	virtual void Tick(float DeltaTime) = 0;

	virtual int PreExit() = 0;
	virtual int Exit() = 0;
	virtual int PostExit() = 0;
};