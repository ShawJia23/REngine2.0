#include "MoveArrow.h"
#include"OperationHandleManage.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Engine/Construction/MacroConstruction.h"
#include"../../Engine/RayCast/RayCastSystem.h"
#include"Path/PathHelper.h"
#include"../../Engine/LoadAsset/ObjectAnalysis.h"
#include"../../Engine/Mesh/SubMesh/MeshGroup.h"
extern GActorObject* SelectedObject;
extern bool bOperationHandleSelect;
extern RMeshComponent* SelectAxisComponent;

RMoveArrow::RMoveArrow()
{

}

void RMoveArrow::CreateMesh()
{
	string MeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/MoveArrow.fbx");

	string AnyAxisMeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/AnyAxis_Type_1.fbx");


	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, XAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, YAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, ZAxisComponent, MeshPath);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, AxisComponent, AnyAxisMeshPath);

	YAxisComponent->SetRotation(frotator(-90.f, 0.f, 0.f));
	XAxisComponent->SetRotation(frotator(0.f, 90.f, 0.f));

	ResetColor();
}

fvector_3d RMoveArrow::AnyAxis(const fvector_3d& InRayWorldOriginPoint, const fvector_3d& InRayWorldDirection, const fvector_3d& InActorWorldOriginPoint)
{
	return fvector_3d(1.f);
}

void RMoveArrow::OnMouseMove(int X, int Y)
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

void RMoveArrow::OnLeftMouseButtonDown(int X, int Y)
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

void RMoveArrow::OnLeftMouseButtonUp(int X, int Y)
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

void RMoveArrow::OnCaptureKeyboardInfor(const RInputKey& InKey)
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
