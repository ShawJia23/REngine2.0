#pragma once
#include"LightComponent.h"
class RMeshComponent;
class RPointLightComponent : public RLightComponent
{
public:
	RPointLightComponent();

	void SetStartAttenuation(float value) { StartAttenuation = value; }
	float GetStartAttenuation() const { return StartAttenuation; }

	void SetEndAttenuation(float value) { EndAttenuation = value; }

	float GetEndAttenuation() const { return EndAttenuation; }
private:
	float StartAttenuation;
	float EndAttenuation;
};
#pragma once
#pragma once
