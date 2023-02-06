#pragma once
#include"../TransformComponent/TransformComponent.h"
#include"../../Interface/DXDeviceInterface.h"
#include"LightType.h"
class RMeshComponent;

class RLightComponent :public RTransformComponent, public IDirectXDeviceInterface
{
	typedef RTransformComponent Super;
	RVARIABLE()
	RMeshComponent* LightMesh;
public:
	RLightComponent();
	virtual ~RLightComponent();

	void SetLightIntensity(const fvector_3d& InNewLightIntensity) { LightIntensity - InNewLightIntensity; }
	const fvector_3d& GetLightIntensity() { return LightIntensity; }

	void SetLightMesh(RMeshComponent* mesh);
	RMeshComponent* GetLightMesh() { return LightMesh; }

	void SetLightType(ELightType lightType) { LightType = lightType; }
	ELightType GetLightType() { return LightType; }

public:
	virtual void SetPosition(const XMFLOAT3& newPosition);
	virtual void SetForwardVector(const XMFLOAT3& forwardVector);
	virtual void SetRightVector(const XMFLOAT3& rightVector);
	virtual void SetUPVector(const XMFLOAT3& upVector);
	virtual void SetRotation(const fvector_3d& InNewRotation);
	virtual void SetScale(const fvector_3d& InNewScale);
protected:
	fvector_3d LightIntensity;
	ELightType LightType;
};

class RParallelLightComponent : public RLightComponent
{
public:
	RParallelLightComponent();
};

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

class RSpotLightComponent : public RLightComponent
{
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