#include "World.h"
#include"../Camera/Camera.h"
#include"Construction/MacroConstruction.h"
RWorld::RWorld()
{
	CreateObjectParam param;
	param.Outer = this;
	m_camera = CreateObject<RCamera>(param,new RCamera());
}
