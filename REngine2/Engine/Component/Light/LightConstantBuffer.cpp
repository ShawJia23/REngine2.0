#include "LightConstantBuffer.h"

RLightConstantBuffer::RLightConstantBuffer()
{
	memset(&SceneLights, 0, sizeof(SceneLights));
}

RLight::RLight()
	:StartAttenuation(1.f)
	, EndAttenuation(10.f)
	, LightType((int)ELightType::ParallelLight)
{

}