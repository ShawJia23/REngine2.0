#pragma once
#include "../../imgui/imgui.h"
class GameTimer;
class EditorLogSystem
{
	friend class LogEditor;
public:
	EditorLogSystem();

	static EditorLogSystem* Get();
	static void Destory();
public:
	void Clear();

	void AddLog(const char* Fmt, ...);
	void AddError(const char* Fmt, ...);
	void AddWarning(const char* Fmt, ...);
	void AddSuccess(const char* Fmt, ...);

protected:
	virtual void Draw(GameTimer& gt);

protected:
	ImGuiTextBuffer TextBuff;
	ImGuiTextFilter TextFikter;
	ImVector<int>	LineOffsets;
	bool bAutoScroll;

protected:
	static EditorLogSystem* LogSystem;
};