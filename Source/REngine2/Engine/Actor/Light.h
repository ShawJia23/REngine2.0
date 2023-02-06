#pragma once
#include"ActorObject.h"
class RLightComponent;
//G -> Game
class GLight :public GActorObject
{
	typedef GActorObject Super;

	RVARIABLE()
	RLightComponent* LightComponent;
public:
	GLight();

	virtual void Tick(float DeltaTime);
public:
	virtual void SetPosition(const XMFLOAT3& InNewPosition);
	virtual void SetRotation(const fvector_3d& InRotation);
	virtual void SetScale(const fvector_3d& InNewScale);
public:
	void SetLightIntensity(const fvector_3d& InNewLightIntensity);

protected:
	virtual void SetLightComponent(RLightComponent* InNewComponent);

public:
	const RLightComponent* GetLightComponent() const { return  LightComponent; }
};


class GParallelLight :public GLight
{
	typedef GLight Super;
public:
	GParallelLight();

	virtual void Tick(float DeltaTime);
};

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