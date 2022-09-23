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

	RCamera* GetCamera() { return m_camera; }
protected:
	RVARIABLE()
	RCamera* m_camera;
};