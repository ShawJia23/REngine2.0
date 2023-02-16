#pragma once
#include"../Actor/ActorObject.h"
#include"Light.CodeReflection.h"
class RLightComponent;
//G -> Game
class GLight :public GActorObject
{
	CODEREFLECTION()

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