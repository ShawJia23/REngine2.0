#include "TransformComponent.h"

RTransformComponent::RTransformComponent()
	:Position(0.f,0.f, 0.f),
	ForwardVector(1.f,0.f,0.f),
	RightVector(0.f,1.f,0.f),
	UpVector(0.f,0.f,1.f)
{

}

void RTransformComponent::SetPosition(const XMFLOAT3& newPosition)
{
	Position = newPosition;
}

void RTransformComponent::SetForwardVector(const XMFLOAT3& forwardVector)
{
	ForwardVector = forwardVector;
}

void RTransformComponent::SetRightVector(const XMFLOAT3& rightVector)
{
	RightVector = rightVector;
}

void RTransformComponent::SetUPVector(const XMFLOAT3& upVector)
{
	UpVector = upVector;
}

void RTransformComponent::CorrectionVector()
{
	XMVECTOR Right = XMLoadFloat3(&RightVector);
	XMVECTOR Up = XMLoadFloat3(&UpVector);
	XMVECTOR Forward = XMLoadFloat3(&ForwardVector);

	Forward = XMVector3Normalize(Forward);
	Up = XMVector3Normalize(XMVector3Cross(Forward, Right));

	Right = XMVector3Cross(Up, Forward);

	XMStoreFloat3(&RightVector, Right);
	XMStoreFloat3(&UpVector, Up);
	XMStoreFloat3(&ForwardVector, Forward);
}

fvector_3d RTransformComponent::GetCorrectionPosition()
{
	fvector_3d F3D;
	GetCorrectionPosition(F3D);

	return F3D;
}

void RTransformComponent::GetCorrectionPosition(fvector_3d& pos3)
{
	XMVECTOR Right = XMLoadFloat3(&RightVector);
	XMVECTOR Up = XMLoadFloat3(&UpVector);
	XMVECTOR Forward = XMLoadFloat3(&ForwardVector);

	XMVECTOR NewPosition = XMLoadFloat3(&Position);

	pos3.x = -XMVectorGetX(XMVector3Dot(NewPosition, Right));
	pos3.y = -XMVectorGetX(XMVector3Dot(NewPosition, Up));
	pos3.z = -XMVectorGetX(XMVector3Dot(NewPosition, Forward));
}