#pragma once
#include"../EditorBase.h"

class GActorObject;
class ObjectExplorerEditor :public EditorBase
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();

	void HighlightDisplayObject(GActorObject* actor);
}; 
