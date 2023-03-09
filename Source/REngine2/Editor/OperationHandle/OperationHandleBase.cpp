#include"OperationHandleBase.h"
#include"OperationHandleManage.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Engine/Component/Input/InputComponent.h"
#include"../../Engine/Materials/Material.h"
#include"../../Engine/World.h"
#include"../../Engine/Camera/Camera.h"
#include"../../Engine/Math/RMath.h"
#include"../../Engine/Construction/MacroConstruction.h"
#include"../../Engine/RayCast/RayCastSystem.h"
extern RMeshComponent* SelectAxisComponent;
extern GActorObject* SelectedObject;
extern bool bOperationHandleSelect;

OperationHandleBase::OperationHandleBase()
{
	bPressRightMouse = false;
	FixedZoom = 30.f;

	BUILD_OBJECT_PARAMETERS(Type, this);

	InputComponent = CreateObject<RInputComponent>(ParamType, new RInputComponent());
	XAxisComponent = ConstructionObject<CustomMeshComponent>(ParamType);
	YAxisComponent = ConstructionObject<CustomMeshComponent>(ParamType);
	ZAxisComponent = ConstructionObject<CustomMeshComponent>(ParamType);
	AxisComponent = ConstructionObject<CustomMeshComponent>(ParamType);

	SetMeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPERATION_HANDLE_POSITION);
}

void OperationHandleBase::SetMeshRenderLayerType(EMeshRenderLayerType InRenderLayerType)
{
	XAxisComponent->SetMeshRenderLayerType(InRenderLayerType);
	YAxisComponent->SetMeshRenderLayerType(InRenderLayerType);
	ZAxisComponent->SetMeshRenderLayerType(InRenderLayerType);
	AxisComponent->SetMeshRenderLayerType(InRenderLayerType);
}

void OperationHandleBase::SetPosition(const XMFLOAT3& InNewPosition)
{
	Super::SetPosition(InNewPosition);

	XAxisComponent->SetPosition(InNewPosition);
	YAxisComponent->SetPosition(InNewPosition);
	ZAxisComponent->SetPosition(InNewPosition);
	AxisComponent->SetPosition(InNewPosition);
}

void OperationHandleBase::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	if (InNewScale >= fvector_3d(0.5f))
	{
		if (XAxisComponent && YAxisComponent && ZAxisComponent)
		{
			XAxisComponent->SetScale(InNewScale);
			YAxisComponent->SetScale(InNewScale);
			ZAxisComponent->SetScale(InNewScale);
			AxisComponent->SetScale(InNewScale);
		}
	}
}

OperationHandleBase::ESelectAxisType OperationHandleBase::GetSelectAxis()
{
	if (SelectAxisComponent)
	{
		if (SelectAxisComponent == XAxisComponent)
		{
			return OperationHandleBase::ESelectAxisType::SELECTAXIS_X;
		}
		else if (SelectAxisComponent == YAxisComponent)
		{
			return OperationHandleBase::ESelectAxisType::SELECTAXIS_Y;
		}
		else if (SelectAxisComponent == ZAxisComponent)
		{
			return OperationHandleBase::ESelectAxisType::SELECTAXIS_Z;
		}
		else if (SelectAxisComponent == AxisComponent)
		{
			return OperationHandleBase::ESelectAxisType::SELECTAXIS_ANY;
		}
	}

	return OperationHandleBase::ESelectAxisType::SELECTAXIS_NONE;
}

void OperationHandleBase::ResetVisible(CustomMeshComponent* InAxisComponent, bool bVisible)
{
	SetVisible(!bVisible);

	InAxisComponent->SetVisible(bVisible);
}

void OperationHandleBase::ResetVisible()
{
	SetVisible(true);
}

void OperationHandleBase::ResetColor()
{
	ResetColor(XAxisComponent, fvector_4d(1.f, 0.f, 0.f, 1.f));//红色
	ResetColor(YAxisComponent, fvector_4d(0.f, 1.f, 0.f, 1.f));//绿色
	ResetColor(ZAxisComponent, fvector_4d(0.f, 0.f, 1.f, 1.f));//蓝色
	ResetColor(AxisComponent, fvector_4d(0.f, 1.f, 1.f, 1.f)); //绿 + 蓝
}

void OperationHandleBase::ResetColor(CustomMeshComponent* InAxisComponent, const fvector_4d& InColor)
{
	if (InAxisComponent)
	{
		if (RMaterial* InMaterial = (*InAxisComponent->GetMaterials())[0])
		{
			InMaterial->SetBaseColor(InColor);
		}
	}
}

void OperationHandleBase::Init()
{
	Super::Init();

	InputComponent->CaptureKeyboardInforDelegate.Bind(this, &OperationHandleBase::OnCaptureKeyboardInfor);
	InputComponent->OnMouseMoveDelegate.Bind(this, &OperationHandleBase::OnMouseMove);
	InputComponent->OnLMouseButtonDownDelegate.Bind(this, &OperationHandleBase::OnLeftMouseButtonDown);
	InputComponent->OnLMouseButtonUpDelegate.Bind(this, &OperationHandleBase::OnLeftMouseButtonUp);
	InputComponent->OnRMouseButtonUpDelegate.Bind(this, &OperationHandleBase::OnRMouseButtonDown);
	InputComponent->OnRMouseButtonUpDelegate.Bind(this, &OperationHandleBase::OnRMouseButtonUp);

	SetVisible(false);
}

void OperationHandleBase::Tick(GameTimer& gt)
{
	Super::Tick(gt);

	if (!GetWorld())
		return;
	if (GetWorld()->GetCamera())
	{
		fvector_3d New3Value = RMath::ToVector3d(GetWorld()->GetCamera()->GetPosition()) - RMath::ToVector3d(GetPosition());
		fvector_3d Scale = New3Value.len() / FixedZoom;

		SetScale(Scale);
	}
}

void OperationHandleBase::SetVisible(bool bNewVisible)
{
	if (XAxisComponent)
		XAxisComponent->SetVisible(bNewVisible);
	if (YAxisComponent)
		YAxisComponent->SetVisible(bNewVisible);
	if (ZAxisComponent)
		ZAxisComponent->SetVisible(bNewVisible);
	if (AxisComponent)
		AxisComponent->SetVisible(bNewVisible);
}

fvector_3d OperationHandleBase::AnyAxis(
	const fvector_3d& InRayWorldOriginPoint,
	const fvector_3d& InRayWorldDirection,
	const fvector_3d& InActorWorldOriginPoint)
{
	return fvector_3d(0.f);
}

fvector_3d OperationHandleBase::GetSelectedObjectDirection(
	const fvector_3d& WorldOriginPoint,
	const fvector_3d& WorldDirection,
	const fvector_3d& ActorWorldPosition)
{
	fvector_3d ActorWorldDir;
	OperationHandleBase::ESelectAxisType AxisType = GetSelectAxis();

	if (true)
	{
		//按世界方向
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			ActorWorldDir = fvector_3d(1.f, 0.f, 0.f);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			ActorWorldDir = fvector_3d(0.f, 1.f, 0.f);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			ActorWorldDir = fvector_3d(0.f, 0.f, 1.f);
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			ActorWorldDir = AnyAxis(
				WorldOriginPoint,
				WorldDirection,
				ActorWorldPosition);
			break;
		}
	}
	else
	{
		//按对象方向
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			ActorWorldDir = RMath::ToVector3d(SelectedObject->GetRightVector());
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			ActorWorldDir = RMath::ToVector3d(SelectedObject->GetUPVector());
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			ActorWorldDir = RMath::ToVector3d(SelectedObject->GetForwardVector());
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			ActorWorldDir = AnyAxis(
				WorldOriginPoint,
				WorldDirection,
				ActorWorldPosition);
			break;
		}
	}

	return ActorWorldDir;
}

void OperationHandleBase::OnMouseMove(int X, int Y)
{
	if (!OperationHandleManage::Get()->IsCaptureMouseNotOnUI())
		return;
	if (!IsCurrentSelectedHandle())
		return;
	if (bOperationHandleSelect)
		return;
	CollisionResult CollisionResult;
	RayCastSystem::HitSpecificObjectsResultByScreen(
		GetWorld(),
		this,
		IgnoreComponents,
		X, Y,
		CollisionResult);

	ResetColor();

	if (CollisionResult.bHit)
	{
		CustomMeshComponent* SelectCustomMeshComponent = dynamic_cast<CustomMeshComponent*>(CollisionResult.Component);

		SelectAxisComponent = SelectCustomMeshComponent;
		ResetColor(SelectCustomMeshComponent, fvector_4d(1.f, 1.f, 0.f, 1.f));
	}
	else
	{
		SelectAxisComponent = nullptr;

		if (!SelectedObject)
		{
			SetVisible(false);
		}
	}
}

void OperationHandleBase::OnLeftMouseButtonDown(int X, int Y)
{

}

void OperationHandleBase::OnLeftMouseButtonUp(int X, int Y)
{

}

void OperationHandleBase::OnRMouseButtonDown(int X, int Y)
{
	bPressRightMouse = true;
}

void OperationHandleBase::OnRMouseButtonUp(int X, int Y)
{
	bPressRightMouse = false;
}

void OperationHandleBase::OnCaptureKeyboardInfor(const RInputKey& InKey)
{
}

float OperationHandleBase::GetMouseCreenMovePosition(
	int X, int Y,
	fvector_3d& ActorWorldPosition,
	fvector_3d& ActorWorldDir)
{
	if (!SelectedObject)
	{
		return -1;
	}

	OperationHandleBase::ESelectAxisType AxisType = GetSelectAxis();
	if (AxisType != OperationHandleBase::ESelectAxisType::SELECTAXIS_NONE)
	{
		XMVECTOR ViewOriginPoint;
		XMVECTOR ViewDirection;
		XMMATRIX ViewInverseMatrix;
		if (RayCastSystem::GetRayParamByScreen(
			GetWorld(),
			fvector_2id(X, Y),
			ViewOriginPoint,
			ViewDirection,
			ViewInverseMatrix))
		{
			XMVECTOR CTORWorldOriginPoint = XMVector3TransformCoord(ViewOriginPoint, ViewInverseMatrix);
			XMVECTOR CTORWorldDirection = XMVector3TransformNormal(ViewDirection, ViewInverseMatrix);

			XMFLOAT3 WorldOriginPointLOAT3;
			XMFLOAT3 WorldDirectionLOAT3;
			XMStoreFloat3(&WorldOriginPointLOAT3, CTORWorldOriginPoint);
			XMStoreFloat3(&WorldDirectionLOAT3, CTORWorldDirection);

			//射线的方向和位置(世界)
			fvector_3d WorldOriginPoint = RMath::ToVector3d(WorldOriginPointLOAT3);
			fvector_3d WorldDirection = RMath::ToVector3d(WorldDirectionLOAT3);

			WorldDirection.normalize();

			ActorWorldPosition = RMath::ToVector3d(SelectedObject->GetPosition());

			ActorWorldDir = GetSelectedObjectDirection(
				WorldOriginPoint,
				WorldDirection,
				ActorWorldPosition);

			fvector_3d V1xV2 = fvector_3d::cross_product(WorldDirection, ActorWorldDir);
			float Len = V1xV2.len();

			return (fvector_3d::dot(
				fvector_3d::cross_product(ActorWorldPosition - WorldOriginPoint, WorldDirection),
				V1xV2) / (Len * Len));
		}
	}

	return -1;
}

bool OperationHandleBase::IsCurrentSelectedHandle()
{
	return this == OperationHandleManage::Get()->GetSelectedOperationHandle();
}

