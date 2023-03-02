#pragma once
#include"../EditorBase.h"
#include"../../Engine/Interface/DXDeviceInterface.h"
class ToolbarEditor :public EditorBase, public IDirectXDeviceInterface
{
public:
	virtual void BuildEditor();
	virtual void DrawEditor(float DeltaTime);
	virtual void ExitEditor();
};