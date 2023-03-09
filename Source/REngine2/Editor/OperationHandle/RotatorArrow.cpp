#include "RotatorArrow.h"
#include"OperationHandleManage.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../Engine/Component/Mesh/SubMeshComponent/PlaneMeshComponent.h"
#include"../../Engine/Construction/MacroConstruction.h"
#include"../../Engine/RayCast/RayCastSystem.h"
#include"../../Engine/Materials/Material.h"
#include"../../Engine/World.h"
#include"../../Engine/Camera/Camera.h"
#include"Path/PathHelper.h"
extern GActorObject* SelectedObject;
extern bool bOperationHandleSelect;
extern RMeshComponent* SelectAxisComponent;

RRotatorArrow::RRotatorArrow()
{
	BUILD_OBJECT_PARAMETERS(Type, this);

	XPlaneComponent = ConstructionObject<PlaneMeshComponent>(ParamType);
	YPlaneComponent = ConstructionObject<PlaneMeshComponent>(ParamType);
	ZPlaneComponent = ConstructionObject<PlaneMeshComponent>(ParamType);

	//射线检测中 希望这些组件不会被检测
	IgnoreComponents.push_back(XPlaneComponent);
	IgnoreComponents.push_back(YPlaneComponent);
	IgnoreComponents.push_back(ZPlaneComponent);

	//指定渲染层级
	XPlaneComponent->SetMeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPERATION_HANDLE_ROTATE);
	YPlaneComponent->SetMeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPERATION_HANDLE_ROTATE);
	ZPlaneComponent->SetMeshRenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPERATION_HANDLE_ROTATE);

	RotatorRatio = 0.f;
	LastT2Value = 0.f;
}

void RRotatorArrow::CreateMesh()
{
	string MeshPathX = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/RotateHandleX.fbx");

	string MeshPathY = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/RotateHandleY.fbx");

	string MeshPathZ = PathHelper::RelativeToAbsolutePath(
		PathHelper::GetEngineAssetModelPath() + "/Handle/RotateHandleZ.fbx");

	//创建操作轴
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, XAxisComponent, MeshPathX);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, YAxisComponent, MeshPathY);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, ZAxisComponent, MeshPathZ);
	CREATE_RENDER_DATA_BY_COMPONENT(CustomMeshComponent, AxisComponent, MeshPathZ);

	//显示CD面片
	CREATE_RENDER_DATA_BY_COMPONENT(PlaneMeshComponent, XPlaneComponent, 5.2, 5.2, 2, 2);
	CREATE_RENDER_DATA_BY_COMPONENT(PlaneMeshComponent, YPlaneComponent, 5.2, 5.2, 2, 2);
	CREATE_RENDER_DATA_BY_COMPONENT(PlaneMeshComponent, ZPlaneComponent, 5.2, 5.2, 2, 2);

	AxisComponent->SetPickup(false);

	//相互垂直
	YPlaneComponent->SetRotation(frotator(90.f, 0.f, 0.f));
	XPlaneComponent->SetRotation(frotator(0.f, 00.f, 0.f));
	ZPlaneComponent->SetRotation(frotator(0.f, 0.f, -90.f));

	//读取材质
	std::string PlaneComponentMaterial = "Rot_Handle_Plane";
	LoadPlaneComponentMaterial(YPlaneComponent, PlaneComponentMaterial);
	LoadPlaneComponentMaterial(XPlaneComponent, PlaneComponentMaterial);
	LoadPlaneComponentMaterial(ZPlaneComponent, PlaneComponentMaterial);

	ResetColor();
}

void RRotatorArrow::LoadPlaneComponentMaterial(RMeshComponent* InComponent, const std::string& InFilename)
{
	if (RMaterial* InMaterial = (*InComponent->GetMaterials())[0])
	{
		InMaterial->SetBaseColor(InFilename);
	}
}

void RRotatorArrow::SetCDValue(RMeshComponent* InComponent, float InValue)
{
	if (RMaterial* InMaterial = (*InComponent->GetMaterials())[0])
	{
		InMaterial->SetFloatParam(0, InValue);
	}
}

void RRotatorArrow::SetCDValue(float InValue)
{
	SetCDValue(YPlaneComponent, InValue);
	SetCDValue(ZPlaneComponent, InValue);
	SetCDValue(XPlaneComponent, InValue);
}

void RRotatorArrow::ResetCDValue()
{
	SetCDValue(0.f);
}

fvector_3d RRotatorArrow::GetSelectedObjectDirection(const fvector_3d& WorldOriginPoint, const fvector_3d& WorldDirection, const fvector_3d& ActorWorldPosition)
{
	fvector_3d ActorWorldDir;
	OperationHandleBase::ESelectAxisType AxisType = GetSelectAxis();

	if (true)
	{
		//按世界方向
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			ActorWorldDir = fvector_3d(0.f, 1.f, 0.f);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			ActorWorldDir = fvector_3d(1.f, 0.f, 0.f);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			ActorWorldDir = fvector_3d(1.f, 0.f, 0.f);
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
			ActorWorldDir = RMath::ToVector3d(SelectedObject->GetUPVector());
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			ActorWorldDir = RMath::ToVector3d(SelectedObject->GetRightVector());
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

void RRotatorArrow::SetScale(const fvector_3d& InNewScale)
{
	Super::SetScale(InNewScale);

	if (InNewScale >= fvector_3d(0.5f))
	{
		if (XAxisComponent && YAxisComponent && ZAxisComponent)
		{
			AxisComponent->SetScale(InNewScale * 1.4f);

			XPlaneComponent->SetScale(InNewScale);
			YPlaneComponent->SetScale(InNewScale);
			ZPlaneComponent->SetScale(InNewScale);
		}
	}
}

void RRotatorArrow::SetPosition(const XMFLOAT3& InNewPosition)
{
	Super::SetPosition(InNewPosition);

	XPlaneComponent->SetPosition(InNewPosition);
	YPlaneComponent->SetPosition(InNewPosition);
	ZPlaneComponent->SetPosition(InNewPosition);
}

void RRotatorArrow::Tick(GameTimer& gt)
{
	Super::Tick(gt);

	if (IsCurrentSelectedHandle())
	{
		XMMATRIX ArrowWorldInverseMatrix;
		RMath::BuildInverseMatrix(
			ArrowWorldInverseMatrix,
			GetPosition(),
			GetScale(),
			GetRightVector(),
			GetUPVector(),
			GetForwardVector());

		FXMVECTOR CameraPosition = XMLoadFloat3(&GetWorld()->GetCamera()->GetPosition());

		XMVECTOR OutLocalOriginPoint = XMVector3TransformCoord(CameraPosition, ArrowWorldInverseMatrix);

		XMFLOAT3 ViewPosition;
		XMStoreFloat3(&ViewPosition, OutLocalOriginPoint);

		Sample8CubeIndex = RMath::GetSample8CubeIndex(
			RMath::ToVector3d(ViewPosition));

		//Engine_Log("Type=%i ", Type);

		switch (Sample8CubeIndex)
		{
		case 0:
			YAxisComponent->SetRotation(frotator(0.f, 90.f, 0.f));//绿
			XAxisComponent->SetRotation(frotator(-90.f, 0, 0.f));//红色
			AxisComponent->SetRotation(frotator());
			ZAxisComponent->SetRotation(frotator());
			break;
		case 1:
			YAxisComponent->SetRotation(frotator(0.f, -180.f, 0.f));//绿
			XAxisComponent->SetRotation(frotator(-90.f, 0, 0.f));//红色
			AxisComponent->SetRotation(frotator(0.f, 0.f, -90.f));
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, -90.f));
			break;
		case 2:
			YAxisComponent->SetRotation(frotator(0.f, -90.f, 0.f));
			XAxisComponent->SetRotation(frotator());
			AxisComponent->SetRotation(frotator(0.f, 0.f, -90.f));
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, -90.f));
			break;
		case 3:
			YAxisComponent->SetRotation(frotator());//绿
			XAxisComponent->SetRotation(frotator());//红色
			AxisComponent->SetRotation(frotator());//青色
			ZAxisComponent->SetRotation(frotator());//蓝色
			break;
		case 4:
			YAxisComponent->SetRotation(frotator(0.f, 90.f, 0.f));//绿
			XAxisComponent->SetRotation(frotator(-180.f, 0, 0.f));//红色
			AxisComponent->SetRotation(frotator(0.f, 0.f, 90.f));//青色
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, 90.f));//蓝色
			break;
		case 5:
			YAxisComponent->SetRotation(frotator(0.f, 180.f, 0.f));//绿
			XAxisComponent->SetRotation(frotator(-180.f, 0, 0.f));//红色
			AxisComponent->SetRotation(frotator(0.f, 0.f, -180.f));//青色
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, -180.f));//蓝色
			break;
		case 6:
			YAxisComponent->SetRotation(frotator(0.f, 0.f, -180.f));//绿
			XAxisComponent->SetRotation(frotator(0.f, 0.f, 180.f));//红色
			AxisComponent->SetRotation(frotator(0.f, 0.f, -180.f));//青色
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, -180.f));//蓝色
			break;
		case 7:
			YAxisComponent->SetRotation(frotator());//绿
			XAxisComponent->SetRotation(frotator(0.f, 0.f, 180.f));//红色
			AxisComponent->SetRotation(frotator(0.f, 0.f, 90.f));//青色
			ZAxisComponent->SetRotation(frotator(0.f, 0.f, 90.f));//蓝色
			break;
		}
	}
}

void RRotatorArrow::Init()
{
	Super::Init();


}

void RRotatorArrow::ResetVisible(CustomMeshComponent* InAxisComponent, bool bVisible)
{
	Super::ResetVisible(InAxisComponent, bVisible);

	OperationHandleBase::ESelectAxisType AxisHandle = GetSelectAxis();
	switch (AxisHandle)
	{
	case OperationHandleBase::SELECTAXIS_X:
		ZPlaneComponent->SetVisible(bVisible);
		break;
	case OperationHandleBase::SELECTAXIS_Y:
		XPlaneComponent->SetVisible(bVisible);
		break;
	case OperationHandleBase::SELECTAXIS_Z:
		YPlaneComponent->SetVisible(bVisible);
		break;
	case OperationHandleBase::SELECTAXIS_ANY:
		break;
	}
}

void RRotatorArrow::ResetVisible()
{
	Super::ResetVisible();

	XPlaneComponent->SetVisible(false);
	YPlaneComponent->SetVisible(false);
	ZPlaneComponent->SetVisible(false);
}

void RRotatorArrow::SetVisible(bool bNewVisible)
{
	Super::SetVisible(bNewVisible);

	XPlaneComponent->SetVisible(false);
	YPlaneComponent->SetVisible(false);
	ZPlaneComponent->SetVisible(false);
}

float RRotatorArrow::GetSymbol(float InValueOffset, bool bFlip)
{
	if (InValueOffset < 0.f)
	{
		return bFlip ? -1 : 1;
	}
	else if (InValueOffset > 0.f)
	{
		return bFlip ? 1 : -1;
	}

	return 0.f;
}

float RRotatorArrow::GetSymbolByCubeIndex(float InValueOffset)
{
	float Symbol = 1.f;
	OperationHandleBase::ESelectAxisType AxisType = GetSelectAxis();

	switch (Sample8CubeIndex)
	{
	case 0:
	case 1:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			break;
		}
		break;
	}
	case 2:
	case 3:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			break;
		}
		break;
	}
	case 4:
	case 5:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			break;
		}
		break;
	}
	case 6:
	case 7:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = GetSymbol(InValueOffset);
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = GetSymbol(InValueOffset, true);
			break;
		case OperationHandleBase::SELECTAXIS_ANY:
			break;
		}
		break;
	}

	}

	return Symbol;
}

float RRotatorArrow::GetSymbolMaterialByCubeIndex(float InValueOffset)
{
	float Symbol = 1.f;
	OperationHandleBase::ESelectAxisType AxisType = GetSelectAxis();

	switch (Sample8CubeIndex)
	{
	case 2:
	case 3:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = -1.f;
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = -1.f;
			break;
		}
		break;
	}
	case 4:
	case 5:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = -1.f;
			break;
		}
		break;
	}
	case 6:
	case 7:
	{
		switch (AxisType)
		{
		case OperationHandleBase::SELECTAXIS_X:
			Symbol = -1.f;
			break;
		case OperationHandleBase::SELECTAXIS_Y:
			Symbol = -1.f;
			break;
		case OperationHandleBase::SELECTAXIS_Z:
			Symbol = -1.f;
			break;
		}

		break;
	}

	}

	return Symbol;
}

float RRotatorArrow::GetAngleRatio(float InAngle)
{
	if (InAngle > 0.f)
	{
		return InAngle / (360.f);
	}
	else if (InAngle < 0.f)
	{
		return (InAngle + 360.f) / (180.f);
	}

	return 0.f;
}

void RRotatorArrow::PrintAix(ESelectAxisType InAxisType)
{
	switch (InAxisType)
	{
	case OperationHandleBase::SELECTAXIS_NONE:
		Engine_Log("Select Axis None");
		break;
	case OperationHandleBase::SELECTAXIS_X:
		Engine_Log("Select Axis X");
		break;
	case OperationHandleBase::SELECTAXIS_Y:
		Engine_Log("Select Axis Y");
		break;
	case OperationHandleBase::SELECTAXIS_Z:
		Engine_Log("Select Axis Z");
		break;
	case OperationHandleBase::SELECTAXIS_ANY:
		Engine_Log("Select Axis Any");
		break;
	}
}

void RRotatorArrow::OnMouseMove(int X, int Y)
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
					ActorWorldDir = OperationHandleBase::GetSelectedObjectDirection(fvector_3d(), fvector_3d(), fvector_3d());

					float CameraAndSelectedDistance =
						(RMath::ToVector3d(GetWorld()->GetCamera()->GetPosition()) -
							RMath::ToVector3d(SelectedObject->GetPosition())).len();

					//摄像机和物体的相对 拖拽相对偏移保持不变
					float DelteRatio = (T2 - LastT2Value) / CameraAndSelectedDistance;

					//每帧的偏移
					float InValueOffset = DelteRatio - RotatorRatio;
					fvector_3d DeltaVector;
					//模型旋转
					{
						//矫正到正确的符号
						float Symbol = GetSymbolByCubeIndex(InValueOffset);

						DeltaVector = ActorWorldDir * Symbol * fabsf(InValueOffset) * 360.f;
					}

					//材质面片旋转
					{
						float SymbolMaterial = GetSymbolMaterialByCubeIndex(InValueOffset);

						SetCDValue(DelteRatio * SymbolMaterial);
					}

					frotator LastRotation;
					frotator DeltaRotation(DeltaVector.y, DeltaVector.z, DeltaVector.x);

					fquat ActorRotQuat;
					fquat DeltaRotQuat;
					ActorRotQuat.object_to_inertia(LastRotation);
					DeltaRotQuat.object_to_inertia(DeltaRotation);

					fquat ResultQuat;
					if (false)
					{

					}
					else
					{
						ResultQuat = DeltaRotQuat * ActorRotQuat;
					}

					frotator Rot;
					Rot.inertia_to_object(ResultQuat);

					//当作世界
					fvector_3d RotVector(Rot.roll, Rot.pitch, Rot.yaw);

					//
					if (true)
					{
						//按世界方向
						XMMATRIX WorldInverseMatrix;
						RMath::BuildInverseMatrix(
							WorldInverseMatrix,
							SelectedObject->GetPosition(),
							SelectedObject->GetScale(),
							SelectedObject->GetRightVector(),
							SelectedObject->GetUPVector(),
							SelectedObject->GetForwardVector());

						XMFLOAT3 XMSelectRot = RMath::ToFloat3(RotVector);
						FXMVECTOR SelectRot = XMLoadFloat3(&XMSelectRot);

						XMVECTOR OutSelectRot = XMVector3TransformNormal(SelectRot, WorldInverseMatrix);

						XMFLOAT3 SelectViewRot;
						XMStoreFloat3(&SelectViewRot, OutSelectRot);

						RotVector = RMath::ToVector3d(SelectViewRot);
					}

					SelectedObject->SetRotation(RotVector);

					RotatorRatio = DelteRatio;
				}
			}
		}
	}
}

void RRotatorArrow::OnLeftMouseButtonDown(int X, int Y)
{
	Super::OnLeftMouseButtonDown(X, Y);

	if (IsCurrentSelectedHandle())
	{
		if (SelectAxisComponent)
		{
			//对CD 做0值的清除
			ResetCDValue();

			ResetVisible(dynamic_cast<CustomMeshComponent*>(SelectAxisComponent), true);

			bOperationHandleSelect = true;

			fvector_3d ActorWorldPosition;
			fvector_3d ActorWorldDir;
			float T2 = GetMouseCreenMovePosition(X, Y, ActorWorldPosition, ActorWorldDir);
			if (T2 != -1)
			{
				RotatorRatio = 0.f;
				LastT2Value = T2;
			}
		}
	}
}

void RRotatorArrow::OnLeftMouseButtonUp(int X, int Y)
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

void RRotatorArrow::OnCaptureKeyboardInfor(const RInputKey& InKey)
{
	if (SelectObject)
	{
		if (InKey.KeyName == "E")
		{
			OperationHandleManage::Get()->DisplaySelectedOperationHandle(this);

			ResetVisible();
		}
	}
}
