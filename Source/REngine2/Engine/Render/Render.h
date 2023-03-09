#pragma once
#include"RObject/RMinimalObject.h"
#include"DX12/d3dx12.h"
#include "../Engine.h"
#if defined(_WIN32)
#include "../Platform/Windows/WindowsEngine.h"
#else
#endif
class IRenderingInterface
{
	friend class WindowsEngine;
public:
	IRenderingInterface();
	virtual ~IRenderingInterface();

	virtual void Init();

	virtual void PreDraw(GameTimer& gt);
	virtual void Draw(GameTimer& gt);
	virtual void PostDraw(GameTimer& gt);
};