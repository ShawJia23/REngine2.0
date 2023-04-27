#pragma once

#include"../../Render/Engine/DXRenderEngine.h"
#if defined(_WIN32)
#include "../../Engine.h"
#include"../../../Timer/GameTimer.h"
#include"../../Core/public_singleton.h"
class DXRenderEngine;
class RWorld;
class EditorEngine;

class RWindowsEngine :public REngine, public PublicSingleton<RWindowsEngine>
{
	friend class IRenderingInterface;
public:
	RWindowsEngine();
	~RWindowsEngine();

	virtual int PreInit(WinMainCommandParameters InParameters);

	virtual int Init(WinMainCommandParameters InParameters);
	virtual int PostInit();

	virtual void Tick(GameTimer& gt) {};
	virtual void Tick();
	virtual void OnResetSize(int width, int height);

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

	HWND GetMainWindowsHandle() { return MianWindowsHandle; }
	bool InitWindows(WinMainCommandParameters InParameters);
	void CalculateFrameStats();

public:
	GameTimer GetTimer() { return m_Timer; }
	std::wstring mMainWndCaption;
protected:
	void WaitGPUCommandQueueComplete();

	HWND MianWindowsHandle;//主windows句柄
	GameTimer m_Timer;
};
#endif