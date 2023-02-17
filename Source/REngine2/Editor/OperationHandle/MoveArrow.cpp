#include "MoveArrow.h"
#include"OperationHandleManage.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Engine/Construction/MacroConstruction.h"
#include"../../Engine/RayCast/RayCastSystem.h"
#include"Path/PathHelper.h"
extern GActorObject* SelectedObject;
extern bool bOperationHandleSelect;
extern RMeshComponent* SelectAxisComponent;

MoveArrow::MoveArrow()
{

}

void MoveArrow::CreateMesh()
{
	string MeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/MoveArrow.fbx");

	string AnyAxisMeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineContentPath() + "/Handle/AnyAxis_Type_1.fbx");

	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, XAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, YAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, ZAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, AxisComponent, AnyAxisMeshPath);
	YAxisComponent->SetRotation(fvector_3d(-90.f, 0.f, 0.f));
	XAxisComponent->SetRotation(fvector_3d(0.f, 90.f, 0.f));

	ResetColor();
}

fvector_3d MoveArrow::AnyAxis(const fvector_3d& InRayWorldOriginPoint, const fvector_3d& InRayWorldDirection, const fvector_3d& InActorWorldOriginPoint)
{
	return fvector_3d(1.f);
}

void MoveArrow::OnMouseMove(int X, int Y)
{
	Super::OnMouseMove(X, Y);

	if (IsCurrentSelectedHandle())
	{
		if (SelectedObject)
		{
			if (bOperationHandleSelect)
			{
				fvector_3d ActorWorldPosition;
				fvector_3d ActorWorldDir;
				float T2 = GetMouseCreenMovePosition(X, Y, ActorWorldPosition, ActorWorldDir);
				if (T2 != -1)
				{
					fvector_3d WorldMovePosition = ActorWorldDir * T2 + ActorWorldPosition + RelativePosition;

					XMFLOAT3 LOAT3Position = RMath::ToFloat3(WorldMovePosition);
					SelectedObject->SetPosition(LOAT3Position);

					SetPosition(LOAT3Position);
				}
			}
		}
	}
}

void MoveArrow::OnLeftMouseButtonDown(int X, int Y)
{
	Super::OnLeftMouseButtonDown(X, Y);

	if (IsCurrentSelectedHandle())
	{
		if (SelectAxisComponent)
		{
			ResetVisible(dynamic_cast<CustomMeshComponent*>(SelectAxisComponent), true);

			bOperationHandleSelect = true;

			fvector_3d ActorWorldPosition;
			fvector_3d ActorWorldDir;
			float T2 = GetMouseCreenMovePosition(X, Y, ActorWorldPosition, ActorWorldDir);
			if (T2 != -1)
			{
				fvector_3d WorldMovePosition = ActorWorldDir * T2 + ActorWorldPosition;

				RelativePosition = ActorWorldPosition - WorldMovePosition;
			}
		}
	}
}

void MoveArrow::OnLeftMouseButtonUp(int X, int Y)
{
	Super::OnLeftMouseButtonUp(X, Y);

	if (IsCurrentSelectedHandle())
	{
		bOperationHandleSelect = false;

		if (SelectAxisComponent)
		{
			ResetVisible();
		}
	}
}

void MoveArrow::OnCaptureKeyboardInfor(const RInputKey& InKey)
{
	if (SelectObject)
	{
		if (!bPressRightMouse)
		{
			if (InKey.KeyName == "W")
			{
				OperationHandleManage::Get()->DisplaySelectedOperationHandle(this);
			}
		}
	}
}
