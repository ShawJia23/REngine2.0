#pragma once

#include"ViewPort/Viewport.h"
#include"RObject/RMinimalObject.h"

struct RInputKey;
class RTransformComponent;
class RInputComponent;
class RCamera;

class RWorld :public RMinimalObject 
{
public:
	RWorld();

	RVARIABLE()
	RCamera* m_camera;
};