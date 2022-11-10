#include "World.h"
#include"../Camera/Camera.h"
#include"Construction/MacroConstruction.h"
RWorld::RWorld()
{
	m_camera = CreateObject<RCamera>(new RCamera());
}
