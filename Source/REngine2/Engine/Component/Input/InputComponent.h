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
	RVARIABLE(hello world)
		RCaptureKeyBoardDelegate CaptureKeyboardInforDelegate;

	RVARIABLE(xxx, aaaa)
		RCaptureOnMouseDelegate OnRMouseButtonDownDelegate;

	RVARIABLE(aaa, vvv)
		RCaptureOnMouseDelegate OnRMouseButtonUpDelegate;

	RVARIABLE(xxx, aaaa)
		RCaptureOnMouseDelegate OnLMouseButtonDownDelegate;

	RVARIABLE(aaa, vvv)
		RCaptureOnMouseDelegate OnLMouseButtonUpDelegate;

	RVARIABLE(xxx, www)
		RCaptureOnMouseDelegate OnMouseMoveDelegate;

	RVARIABLE(xxx, www)
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

