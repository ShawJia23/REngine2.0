#pragma once
#include"../ActorObject.h"
#include"Light.h"

class GSpotLight :public GLight
{
	typedef GLight Super;
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
