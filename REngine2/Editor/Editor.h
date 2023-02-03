#pragma once
#include "../Engine/Engine.h"
#include "EditorBase.h"
#include "Log/LogEditor.h"
#include "Toolbar/ToolbarEditor.h"
#include"Explorer/ObjectExplorer.h"
class EditorEngine
	:public REngine
	, public EditorBase
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

	virtual void Tick(float DeltaTime) {};

	virtual int PreExit();
	virtual int Exit();
	virtual int PostExit();

public:
	virtual void BuildEditor();
	virtual void DrawEditor(float DeltaTime);
	virtual void ExitEditor();

public:
	void DrawLayer(float DeltaTime);

protected:
	class ToolbarEditor* m_ToolbarEditor;
	class LogEditor* m_LogEditor;
	class ObjectExplorerEditor* m_ObjectExplorerEditor;
};