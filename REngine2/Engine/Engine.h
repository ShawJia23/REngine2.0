#pragma once

#include"RObject/RMinimalObject.h"

#if defined(_WIN32)
#include"Platform/Windows/WinMainCommandParameters.h"
#endif // 1

class REngine:public RMinimalObject
{
public:
	REngine();
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