#pragma once

#include"../../Render/Engine/DXRenderEngine.h"
#if defined(_WIN32)
#include "../../Engine.h"
#include"../../../Timer/GameTimer.h"

class DXRenderEngine;
class RWorld;
class RMeshManage;
class RLightManage;
class EditorEngine;

class RWindowsEngine :public REngine
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

	DXRenderEngine* GetRenderEngine() { return m_renderEngine; }
	HWND GetMainWindowsHandle() { return MianWindowsHandle; }
	bool InitWindows(WinMainCommandParameters InParameters);
	void CalculateFrameStats();
#if EDITOR_ENGINE
	EditorEngine* GetEditorEngine() { return m_EditorEngine; }
#endif

public:
	RMeshManage* GetMeshManage();
	RLightManage* GetLightManage();
	RTextureManage* GetTextureManage();
	RWorld* GetWorld() { return m_world; }
	GameTimer GetTimer() { return m_Timer; }
	std::wstring mMainWndCaption;
protected:
	void WaitGPUCommandQueueComplete();

	HWND MianWindowsHandle;//主windows句柄
	DXRenderEngine* m_renderEngine;
	GameTimer m_Timer;
#if EDITOR_ENGINE
	class EditorEngine* m_EditorEngine;
#endif
	RWorld* m_world;
};
#endif