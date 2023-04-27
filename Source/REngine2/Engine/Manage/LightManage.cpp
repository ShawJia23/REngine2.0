#include"LightManage.h"
#include"../Component/Light/LightComponent.h"
RLightManage::RLightManage()
{
}
RLightManage::~RLightManage()
{
	Clear();
}
void RLightManage::AddLight(RLightComponent* lightComponent)
{
	Lights.push_back(lightComponent);
}
void RLightManage::Clear()
{
	Lights.clear();
	Lights.shrink_to_fit();
}