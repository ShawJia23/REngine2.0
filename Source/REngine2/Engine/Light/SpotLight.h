#pragma once
#include"Light.h"
#include"SpotLight.CodeReflection.h"
class GSpotLight :public GLight
{
	CODEREFLECTION()
public:
	GSpotLight();

	virtual void Tick(float DeltaTime);

	float GetStartAttenuation() const;
	float GetEndAttenuation() const;
	float GetInnerCorner() const;
	float GetOuterCorner() const;

	void SetStartAttenuation(float InNewStartAttenuation);
	void SetEndAttenuation(float InNewEndAttenuation);
	void SetInnerCorner(float innerCorner);
	void SetOuterCorner(float outerCorner);
};