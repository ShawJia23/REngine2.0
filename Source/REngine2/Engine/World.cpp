#include "World.h"
#include"Camera/Camera.h"
#include"Construction/MacroConstruction.h"
RWorld::RWorld()
{
	BUILD_OBJECT_PARAMETERS_BY_NO_COMPONENT(this);
	m_camera = CreateObject<RCamera>(inObjectParam,new RCamera());
	m_camera->SetPosition(XMFLOAT3(0, 10, -40));
}

RWorld::~RWorld()
{
	ActorObjects.clear();
	ActorObjects.shrink_to_fit();
}
