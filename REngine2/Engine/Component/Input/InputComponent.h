#pragma once

#include"../RComponent.h"
#include"../../EngineMinimal.h"
#include"RInputType.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureKeyBoardDelegate, void, const RInputKey &);
DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureOnMouseDelegate, void, int, int);
DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureOnMouseWheelDelegate, void, int, int, float);

class RInputComponent:public RComponent
{
public:
	RVARIABLE(hello world)
		RCaptureKeyBoardDelegate CaptureKeyboardInforDelegate;

	RVARIABLE(xxx, aaaa)
		RCaptureOnMouseDelegate OnMouseButtonDownDelegate;

	RVARIABLE(aaa, vvv)
		RCaptureOnMouseDelegate OnMouseButtonUpDelegate;

	RVARIABLE(xxx, www)
		RCaptureOnMouseDelegate OnMouseMoveDelegate;

	RVARIABLE(xxx, www)
		RCaptureOnMouseWheelDelegate OnMouseWheelDelegate;


	virtual void Init();
	virtual void Tick(float DeltaTime);

	virtual void OnMouseButtonDown(int X, int Y);
	virtual void OnMouseButtonUp(int X, int Y);
	virtual void OnMouseMove(int X, int Y);
	virtual void OnMouseWheel(int X, int Y, float InDelta);
};

