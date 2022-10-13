#pragma once

#include"RComponent/RComponent.h"

class RTransformComponent :public RComponent 
{
public:
	RTransformComponent();

	void SetPosition(const XMFLOAT3& newPosition);
	void SetForwardVector(const XMFLOAT3& forwardVector);
	void SetRightVector(const XMFLOAT3& rightVector);
	void SetUPVector(const XMFLOAT3& upVector);
	void SetRotation(const fvector_3d& InNewRotation);
	void SetScale(const fvector_3d& InNewScale);

	XMFLOAT3& GetPosition() { return Position; }
	XMFLOAT3& GetForwardVector() { return ForwardVector; }
	XMFLOAT3& GetRightVector() { return RightVector; }
	XMFLOAT3& GetUPVector() { return UpVector; }
	fvector_3d GetRotation() const { return fvector_3d(Rotation.x, Rotation.y, Rotation.z); }
	fvector_3d GetScale() const { return fvector_3d(Scale.x, Scale.y, Scale.z); }

	//����Up right look(fd) ���� pos
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