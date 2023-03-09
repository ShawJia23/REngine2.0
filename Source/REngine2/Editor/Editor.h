#pragma once
#include "../Engine/Engine.h"
#include "EditorBase.h"
#include "Log/LogEditor.h"
#include "Toolbar/ToolbarEditor.h"
#include"Explorer/ObjectExplorer.h"
#include"Inspector/InspectorEditor.h"
class EditorEngine:public REngine, public EditorBase
{
public:
	EditorEngine();

	virtual int PreInit(
#if defined(_WIN32)
		WinMainCommandParameters InParameters
#endif // 1
	);

	virtual int Init(
#if defined(_WIN32)
		WinMainCommandParameters InParameters
#endif // 1
	);
	virtual int PostInit();

	virtual void Tick(GameTimer& gt) {};
	virtual void Tick() {};
	virtual void OnResetSize(int width, int height) {};
	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();

public:
	void DrawLayer(GameTimer& gt);

public:
	class ToolbarEditor* m_ToolbarEditor;
	class LogEditor* m_LogEditor;
	class ObjectExplorerEditor* m_ObjectExplorerEditor;
	class InspectorEditor* m_InspectorEditor;
};