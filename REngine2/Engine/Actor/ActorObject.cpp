#include"ActorObject.h"
#include"../Component/TransformComponent/TransformComponent.h"


GActorObject::GActorObject()
{
	CreateObjectParam param;
	param.Outer = this;
	TransformationComponent = CreateObject<RTransformComponent>(param,new RTransformComponent());
}

void GActorObject::SetPosition(const XMFLOAT3& InNewPosition)
{
	TransformationComponent->SetPosition(InNewPosition);
}

void GActorObject::SetRotation(const fvector_3d& InRotation)
{
	TransformationComponent->SetRotation(InRotation);
}

void GActorObject::SetScale(const fvector_3d& InNewScale)
{
	TransformationComponent->SetScale(InNewScale);
}

XMFLOAT3& GActorObject::GetPosition()
{
	return TransformationComponent->GetPosition();
}

XMFLOAT3& GActorObject::GetForwardVector()
{
	return TransformationComponent->GetForwardVector();
}

XMFLOAT3& GActorObject::GetRightVector()
{
	return TransformationComponent->GetRightVector();
}

XMFLOAT3& GActorObject::GetUPVector()
{
	return TransformationComponent->GetUPVector();
}

fvector_3d GActorObject::GetRotation() const
{
	return TransformationComponent->GetRotation();
}

fvector_3d GActorObject::GetScale() const
{
	return TransformationComponent->GetScale();
}
