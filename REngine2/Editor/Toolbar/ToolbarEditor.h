#pragma once
#include"../EditorBase.h"

class ToolbarEditor :public EditorBase
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(float DeltaTime);
	virtual void ExitEditor();

public:
	void NewLevel();
};