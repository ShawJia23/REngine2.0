#pragma once
#include "../EditorBase.h"

class LogEditor :public EditorBase
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(float DeltaTime);
	virtual void ExitEditor();
};