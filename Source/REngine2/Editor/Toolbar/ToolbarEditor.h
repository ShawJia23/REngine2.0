#pragma once
#include"../EditorBase.h"
class ToolbarEditor :public EditorBase
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();
};