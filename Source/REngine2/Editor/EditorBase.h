#pragma once
#include"../Engine/EngineMinimal.h"

class EditorBase
{
public:
	EditorBase();
	virtual void BuildEditor() = 0;
	virtual void DrawEditor(GameTimer& gt) = 0;
	virtual void ExitEditor() = 0;
	virtual void RenderEnd();
	virtual void RenderStart();
	bool bOpen;
};