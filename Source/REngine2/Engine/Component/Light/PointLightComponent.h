#pragma once
#include"LightComponent.h"
#include"PointLightComponent.CodeReflection.h"

class RPointLightComponent : public RLightComponent
{
	CODEREFLECTION()
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