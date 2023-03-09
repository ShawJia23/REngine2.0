#pragma once
#include "../EditorBase.h"

class LogEditor :public EditorBase
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();
	virtual void RenderEnd();
};