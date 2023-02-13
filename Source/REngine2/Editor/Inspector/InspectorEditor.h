#pragma once
#include "../EditorBase.h"

class InspectorEditor :public EditorBase
{
public:
	InspectorEditor();

public:
	virtual void BuildEditor();
	virtual void DrawEditor(float DeltaTime);
	virtual void ExitEditor();

private:
	class GActorObject* LastSelectedObject;
};