#include "OperationHandleManage.h"
#include"OperationHandleBase.h"
#if EDITOR_ENGINE
#include"../../Editor/OperationHandle/MoveArrow.h"
#include"../../Editor/OperationHandle/RotatorArrow.h"
#include"../../Editor/OperationHandle/ScalingArrow.h"
#include"../../Common/EngineEditorCommon.h"
#include"../../Engine/Actor/ActorObject.h"
extern class RMoveArrow* MoveArrow;
//extern class RScalingArrow* ScalingArrow;
//extern class RRotatorArrow* RotatorArrow;
extern class GActorObject* SelectedObject;

OperationHandleManage* OperationHandleManage::InManage = nullptr;

OperationHandleManage::OperationHandleManage()
{

}

OperationHandleManage* OperationHandleManage::Get()
{
	if (!InManage)
	{
		InManage = new OperationHandleManage();
	}

	return InManage;
}

void OperationHandleManage::Destroy()
{
	if (InManage)
	{
		delete InManage;
		InManage = nullptr;
	}
}

void OperationHandleManage::AllOperationHandleHide()
{
	MoveArrow->SetVisible(false);
	//ScalingArrow->SetVisible(false);
	//RotatorArrow->SetVisible(false);
}

void OperationHandleManage::DisplaySelectedOperationHandle(GActorObject* InNewSelectedObject)
{
	if (SelectedObject)
	{
		//隐藏所有手柄
		AllOperationHandleHide();

		//操作手柄附加到对象身上
		if (OperationHandleBase* InHandleBase = dynamic_cast<OperationHandleBase*>(InNewSelectedObject))
		{
			InHandleBase->SetPosition(SelectedObject->GetPosition());
			//InHandleBase->SetRotation(SelectedObject->GetRotation());
			InHandleBase->SetVisible(true);
		}

		//记录操作手柄
		SetNewSelectedOperationHandle(InNewSelectedObject);
	}
}

void OperationHandleManage::DisplaySelectedOperationHandle()
{
	if (!SelectedObject)
		return;
	if (!SelectedOperationHandle)
	{
		if (MoveArrow)
		{
			MoveArrow->SetPosition(SelectedObject->GetPosition());
			//MoveArrow->SetRotation(SelectedObject->GetRotation());
			MoveArrow->SetVisible(true);

			SetNewSelectedOperationHandle(MoveArrow);
		}
	}
	else
	{
		if (OperationHandleBase* InHandleBase = dynamic_cast<OperationHandleBase*>(SelectedOperationHandle))
		{
			InHandleBase->SetPosition(SelectedObject->GetPosition());
			//InHandleBase->SetRotation(SelectedObject->GetRotation());
			InHandleBase->SetVisible(true);
		}
	}
}

void OperationHandleManage::HideSelectedOperationHandle()
{
	if (OperationHandleBase* InHandleBase = dynamic_cast<OperationHandleBase*>(SelectedOperationHandle))
	{
		InHandleBase->SetVisible(false);
	}
}

void OperationHandleManage::SetNewSelectedOperationHandle(GActorObject* InNewSelectedObject)
{
	SelectedOperationHandle = InNewSelectedObject;
}

void OperationHandleManage::SetNewSelectedObject(GActorObject* InNewSelectedObject)
{
	SelectedObject = InNewSelectedObject;
}

GActorObject* OperationHandleManage::GetSelectedOperationHandle()
{
	return SelectedOperationHandle;
}

bool OperationHandleManage::IsCaptureMouseNotOnUI()
{
	ImGuiIO& IO = ImGui::GetIO();
	return !IO.WantCaptureMouseUnlessPopupClose;
}

#endif