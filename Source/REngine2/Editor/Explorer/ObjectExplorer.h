#pragma once
#include"../EditorBase.h"
#include"../../Engine/Interface/DXDeviceInterface.h"

class GActorObject;
class ObjectExplorerEditor :public EditorBase, public IDirectXDeviceInterface
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(GameTimer& gt);
	virtual void ExitEditor();

	void HighlightDisplayObject(GActorObject* actor);
}; 
