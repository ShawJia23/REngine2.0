#include "World.h"
#include"Camera.h"

RWorld::RWorld()
{
	m_camera = CreateObject<RCamera>(new RCamera());
}
