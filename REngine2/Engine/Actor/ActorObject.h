#pragma once
#include"RObject/RMinimalObject.h"
#include"../EngineMinimal.h"
class RTransformComponent;

class GActorObject :public RMinimalObject
{
	RVARIABLE()
		RTransformComponent* TransformationComponent;

public:
	GActorObject();

public:
	FORCEINLINE RTransformComponent* GetTransformationComponent() const { return TransformationComponent; }
public:
	void SetPosition(const XMFLOAT3& InNewPosition);
	void SetRotation(const fvector_3d& InRotation);
	void SetScale(const fvector_3d& InNewScale);

public:
	XMFLOAT3& GetPosition();
	fvector_3d GetRotation()const;
	fvector_3d GetScale()const;

	XMFLOAT3& GetForwardVector();
	XMFLOAT3& GetRightVector();
	XMFLOAT3& GetUPVector();
};