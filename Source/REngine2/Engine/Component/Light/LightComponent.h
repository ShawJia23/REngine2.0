#pragma once
#include"../TransformComponent/TransformComponent.h"
#include"../../Interface/DXDeviceInterface.h"
#include"LightType.h"
#include"LightComponent.CodeReflection.h"
class RMeshComponent;

class RLightComponent :public RTransformComponent, public IDirectXDeviceInterface
{
	CODEREFLECTION()

	RVARIABLE()
	RMeshComponent* LightMesh;
public:
	RLightComponent();
	virtual ~RLightComponent();

	void SetLightIntensity(const fvector_3d& InNewLightIntensity) { LightIntensity - InNewLightIntensity; }
	const fvector_3d& GetLightIntensity() { return LightIntensity; }

	void SetLightMesh(RMeshComponent* mesh);
	void SetLightType(ELightType lightType) { LightType = lightType; }

	RMeshComponent* GetLightMesh() { return LightMesh; }
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