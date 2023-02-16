#pragma once
#include"LightComponent.h"
#include"SpotLightComponent.CodeReflection.h"

class RSpotLightComponent : public RLightComponent
{
	CODEREFLECTION()
public:
	RSpotLightComponent();

	void SetStartAttenuation(float value) { m_StartAttenuation = value; }
	float GetStartAttenuation() const { return m_StartAttenuation; }

	void SetEndAttenuation(float value) { m_EndAttenuation = value; }
	float GetEndAttenuation() const { return m_EndAttenuation; }

	void SetOuterCorner(float outerCorner);
	float GetOuterCorner() const { return m_OuterCorner; }

	void SetInnerCorner(float innerCorner);
	float GetInnerCorner() const { return m_InnerCorner; }

private:
	float m_StartAttenuation;
	float m_EndAttenuation;

	float m_InnerCorner;
	float m_OuterCorner;
};