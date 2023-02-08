#pragma once
#include"../../Engine.h"

DEFINITION_MULTICAST_SINGLE_DELEGATE(FCaptureOnMousesDelegate, void, int, int);
DEFINITION_MULTICAST_SINGLE_DELEGATE(FCaptureOnMousesWheelsDelegate, void, int, int, float);

extern FCaptureOnMousesWheelsDelegate MousesWheelsDelegate;
extern FCaptureOnMousesDelegate RMouseDownDelegate;
extern FCaptureOnMousesDelegate RMouseUpDelegate;
extern FCaptureOnMousesDelegate LMouseDownDelegate;
extern FCaptureOnMousesDelegate LMouseUpDelegate;
extern FCaptureOnMousesDelegate MouseMoveDelegate;
extern FCaptureOnMousesDelegate ResizeScreenDelegate;