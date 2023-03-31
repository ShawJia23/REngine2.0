#include "ScalingArrow.h"
#include"OperationHandleManage.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Engine/Construction/MacroConstruction.h"
#include"../../Engine/RayCast/RayCastSystem.h"
#include"Path/PathHelper.h"

extern GActorObject* SelectedObject;
extern bool bOperationHandleSelect;
extern RMeshComponent* SelectAxisComponent;

RScalingArrow::RScalingArrow()
{
	LastT2Value = 0.f;
}

void RScalingArrow::CreateMesh()
{
	string MeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/ScalingArrow.fbx");

	string AnyAxisMeshPath = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/AnyAxis_Type_1.fbx");

	MeshRenderData pData;
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, XAxisComponent, MeshPath, pData);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, YAxisComponent, MeshPath, pData);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, ZAxisComponent, MeshPath, pData);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, AxisComponent,AnyAxisMeshPath, pData);

	YAxisComponent->SetRotation(frotator(-90.f, 0.f, 0.f));
	XAxisComponent->SetRotation(frotator(0.f, 90.f, 0.f));

	ResetColor();
}

fvector_3d RScalingArrow::AnyAxis(const fvector_3d& InRayWorldOriginPoint, const fvector_3d& InRayWorldDirection, const fvector_3d& InActorWorldOriginPoint)
{
	return fvector_3d(1.f);
}

void RScalingArrow::OnMouseMove(int X, int Y)
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
					fvector_3d CurrentScale = SelectedObject->GetScale();

					float InValueOffset = T2 - LastT2Value;

					//Engine_Log("InValueOffset =%f", InValueOffset)

					float Value = 0.f;
					if (InValueOffset < 0.f)
					{
						Value = -0.25f;
					}
					else if (InValueOffset > 0.f)
					{
						Value = 0.25f;
					}

					CurrentScale += (ActorWorldDir * Value);

					SelectedObject->SetScale(CurrentScale);

					LastT2Value = T2;
				}
			}
		}
	}
}

void RScalingArrow::OnLeftMouseButtonDown(int X, int Y)
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
				LastT2Value = T2;
			}
		}
	}
}

void RScalingArrow::OnLeftMouseButtonUp(int X, int Y)
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

void RScalingArrow::OnCaptureKeyboardInfor(const RInputKey& InKey)
{
	if (SelectObject)
	{
		if (InKey.KeyName == "R")
		{
			OperationHandleManage::Get()->DisplaySelectedOperationHandle(this);
		}
	}
}
