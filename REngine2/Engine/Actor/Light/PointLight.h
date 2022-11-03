#pragma once
#include"../ActorObject.h"
#include"Light.h"

class GPointLight :public GLight
{
	typedef GLight Super;
public:
	GPointLight();

	virtual void Tick(float DeltaTime);

	float GetStartAttenuation() const;
	float GetEndAttenuation() const;

	void SetStartAttenuation(float InNewStartAttenuation);
	void SetEndAttenuation(float InNewEndAttenuation);
};
#pragma once
