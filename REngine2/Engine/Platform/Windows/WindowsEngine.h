#pragma once

#include"../../Render/Engine/DXRenderEngine.h"
#if defined(_WIN32)
#include "../../Core/Engine.h"

class DXRenderEngine;
class RWorld;
class RWindowsEngine :public REngine
{
	friend class IRenderingInterface;
public:
	RWindowsEngine();
	~RWindowsEngine();

	virtual int PreInit(WinMainCommandParameters InParameters);

	virtual int Init(WinMainCommandParameters InParameters);
	virtual int PostInit();

	virtual void Tick(float DeltaTime);

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

	DXRenderEngine* GetRenderEngine() { return m_renderEngine; }
	HWND GetMainWindowsHandle() { return MianWindowsHandle; }
	bool InitWindows(WinMainCommandParameters InParameters);

protected:
	void WaitGPUCommandQueueComplete();

	HWND MianWindowsHandle;//主windows句柄
	DXRenderEngine* m_renderEngine;
	RWorld* m_world;
};
#endif