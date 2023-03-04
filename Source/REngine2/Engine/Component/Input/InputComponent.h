#pragma once

#include"Component/RComponent.h"
#include"../../EngineMinimal.h"
#include"RInputType.h"
#include"InputComponent.CodeReflection.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureKeyBoardDelegate, void, const RInputKey &);
DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureOnMouseDelegate, void, int, int);
DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureOnMouseWheelDelegate, void, int, int, float);

class RInputComponent:public RComponent
{
	CODEREFLECTION()
public:
	RCaptureKeyBoardDelegate CaptureKeyboardInforDelegate;
	RCaptureOnMouseDelegate OnRMouseButtonDownDelegate;
	RCaptureOnMouseDelegate OnRMouseButtonUpDelegate;
	RCaptureOnMouseDelegate OnLMouseButtonDownDelegate;
	RCaptureOnMouseDelegate OnLMouseButtonUpDelegate;
	RCaptureOnMouseDelegate OnMouseMoveDelegate;
	RCaptureOnMouseWheelDelegate OnMouseWheelDelegate;

	virtual void Init();
	virtual void Tick(float DeltaTime);

	virtual void OnRMouseButtonDown(int X, int Y);
	virtual void OnRMouseButtonUp(int X, int Y);
	virtual void OnLMouseButtonDown(int X, int Y);
	virtual void OnLMouseButtonUp(int X, int Y);
	virtual void OnMouseMove(int X, int Y);
	virtual void OnMouseWheel(int X, int Y, float InDelta);
};

