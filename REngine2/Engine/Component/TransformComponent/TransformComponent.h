#pragma once

#include"../RComponent.h"

class RTransformComponent :public RComponent 
{
public:
	RTransformComponent();

	virtual void SetPosition(const XMFLOAT3& newPosition);
	virtual void SetForwardVector(const XMFLOAT3& forwardVector);
	virtual void SetRightVector(const XMFLOAT3& rightVector);
	virtual void SetUPVector(const XMFLOAT3& upVector);
	virtual void SetRotation(const fvector_3d& InNewRotation);
	virtual void SetScale(const fvector_3d& InNewScale);

	XMFLOAT3& GetPosition() { return Position; }
	XMFLOAT3& GetForwardVector() { return ForwardVector; }
	XMFLOAT3& GetRightVector() { return RightVector; }
	XMFLOAT3& GetUPVector() { return UpVector; }
	fvector_3d GetRotation() const { return fvector_3d(Rotation.x, Rotation.y, Rotation.z); }
	fvector_3d GetScale() const { return fvector_3d(Scale.x, Scale.y, Scale.z); }

	//????Up right look(fd) ???? pos
	void CorrectionVector();

	fvector_3d GetCorrectionPosition();
	void GetCorrectionPosition(fvector_3d& pos3);
private:
	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;
	XMFLOAT3 ForwardVector;
	XMFLOAT3 RightVector;
	XMFLOAT3 UpVector;
};