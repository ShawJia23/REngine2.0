#pragma once
#include "../../Engine.h"

class RenderingEngine : public REngine
{
public:
	void SetMianWindowsHandle(HWND InNewMianWindowsHandle);

protected:
	HWND MianWindowsHandle;
};