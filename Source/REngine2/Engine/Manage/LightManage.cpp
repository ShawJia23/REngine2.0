#include"LightManage.h"
#include"../Component/Light/LightComponent.h"
void RLightManage::AddLight(RLightComponent* lightComponent)
{
	Lights.push_back(lightComponent);
}
