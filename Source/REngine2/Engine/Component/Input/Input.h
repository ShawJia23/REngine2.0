#pragma once
#include"../../Engine.h"

DEFINITION_MULTICAST_SINGLE_DELEGATE(RCaptureOnMousesDelegate, void, int, int);
DEFINITION_MULTICAST_SINGLE_DELEGATE(RCaptureOnMousesWheelsDelegate, void, int, int, float);

extern RCaptureOnMousesWheelsDelegate MousesWheelsDelegate;
extern RCaptureOnMousesDelegate RMouseDownDelegate;
extern RCaptureOnMousesDelegate RMouseUpDelegate;
extern RCaptureOnMousesDelegate LMouseDownDelegate;
extern RCaptureOnMousesDelegate LMouseUpDelegate;
extern RCaptureOnMousesDelegate MouseMoveDelegate;
extern RCaptureOnMousesDelegate ResizeScreenDelegate;