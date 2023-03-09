#pragma once
#include "../EditorBase.h"

class InspectorEditor :public EditorBase
{
public:
	InspectorEditor();

public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();

private:
	class GActorObject* LastSelectedObject;
};