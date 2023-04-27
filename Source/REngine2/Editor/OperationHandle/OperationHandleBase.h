#pragma once
#include"../../Engine/Actor/ActorObject.h"
#include"../../Engine/Component/Input/RInputType.h"
#include "OperationHandleBase.CodeReflection.h"
class CustomMeshComponent;
class RInputComponent;
enum class EMeshRenderLayerType;
class RComponent;

class OperationHandleBase :public GActorObject
{
	CODEREFLECTION()
protected:
	enum ESelectAxisType
	{
		SELECTAXIS_NONE,
		SELECTAXIS_X,//x
		SELECTAXIS_Y,//y
		SELECTAXIS_Z,//z
		SELECTAXIS_ANY,//z
	};

protected:
	RVARIABLE()
	RInputComponent* InputComponent;

	RVARIABLE()
	CustomMeshComponent* XAxisComponent;

	RVARIABLE()
	CustomMeshComponent* YAxisComponent;

	RVARIABLE()
	CustomMeshComponent* ZAxisComponent;

	RVARIABLE()
	CustomMeshComponent* AxisComponent;
public:
	OperationHandleBase();

	virtual void SetMeshRenderLayerType(EMeshRenderLayerType InRenderLayerType);

public:
	virtual void SetPosition(const XMFLOAT3& InNewPosition);
	virtual void SetScale(const fvector_3d& InNewScale);

public:
	ESelectAxisType GetSelectAxis();
	void ResetVisible(CustomMeshComponent* InAxisComponent, bool bVisible);
	void ResetVisible();
	void ResetColor();
	void ResetColor(CustomMeshComponent* InAxisComponent, const fvector_4d& InColor);

public:
	virtual void Init();
	virtual void Tick(GameTimer& gt);
	virtual void SetVisible(bool bNewVisible);
	// virtual bool IsVisible()const;

protected:
	virtual fvector_3d AnyAxis(
		const fvector_3d& InRayWorldOriginPoint,
		const fvector_3d& InRayWorldDirection,
		const fvector_3d& InActorWorldOriginPoint);

	virtual fvector_3d GetSelectedObjectDirection(
		const fvector_3d& WorldOriginPoint,
		const fvector_3d& WorldDirection,
		const fvector_3d& ActorWorldPosition);

protected:
	virtual void OnMouseMove(int X, int Y);
	virtual void OnLeftMouseButtonDown(int X, int Y);
	virtual void OnLeftMouseButtonUp(int X, int Y);
	virtual void OnRMouseButtonDown(int X, int Y);//Right
	virtual void OnRMouseButtonUp(int X, int Y);//Right
	virtual void OnCaptureKeyboardInfor(const RInputKey& InKey);

protected:
	//通过屏幕映射到物体企图移动的下一个位置
	float GetMouseCreenMovePosition(int X, int Y,
		fvector_3d& ActorWorldPosition,
		fvector_3d& ActorWorldDir);

	bool IsCurrentSelectedHandle();

protected:
	float FixedZoom;
	std::vector<RComponent*> IgnoreComponents;
	bool bPressRightMouse;
};