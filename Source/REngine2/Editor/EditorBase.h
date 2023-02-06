#pragma once
#include"../Engine/EngineMinimal.h"

class EditorBase
{
public:
	virtual void BuildEditor() = 0;
	virtual void DrawEditor(float DeltaTime) = 0;
	virtual void ExitEditor() = 0;
};