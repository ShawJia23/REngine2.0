#pragma once
#include"../Core/RObject/RMinimalObject.h"
#include"DX12/d3dx12.h"
#include "../Core/Engine.h"
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

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);
};