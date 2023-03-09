#pragma once
#include"Light.h"
#include"PointLight.CodeReflection.h"
class GPointLight :public GLight
{
	CODEREFLECTION()
public:
	GPointLight();

	virtual void Tick(GameTimer& gt);

	float GetStartAttenuation() const;
	float GetEndAttenuation() const;

	void SetStartAttenuation(float InNewStartAttenuation);
	void SetEndAttenuation(float InNewEndAttenuation);
};