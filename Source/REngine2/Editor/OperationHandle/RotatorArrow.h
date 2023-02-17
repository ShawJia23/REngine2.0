#pragma once
#include "OperationHandleBase.h"

class PlaneMeshComponent;
class RMeshComponent;
class RotatorArrow :public OperationHandleBase
{
	CODEREFLECTION()

	RVARIABLE()
	PlaneMeshComponent* XPlaneComponent;

	RVARIABLE()
	PlaneMeshComponent* YPlaneComponent;

	RVARIABLE()
	PlaneMeshComponent* ZPlaneComponent;

public:
	RotatorArrow();

	void CreateMesh();

	void LoadPlaneComponentMaterial(RMeshComponent* InComponent, const std::string& InFilename);

protected:
	void SetCDValue(RMeshComponent* InComponent, float InValue);
	void SetCDValue(float InValue);
	void ResetCDValue();

protected:
	virtual fvector_3d GetSelectedObjectDirection(
		const fvector_3d& WorldOriginPoint,
		const fvector_3d& WorldDirection,
		const fvector_3d& ActorWorldPosition);

protected:
	virtual void Tick(float DeltaTime);
	virtual void BeginInit();
public:
	virtual void ResetVisible(CustomMeshComponent* InAxisComponent, bool bVisible);
	virtual void ResetVisible();
	virtual void SetVisible(bool bNewVisible);
protected:
	virtual void SetScale(const fvector_3d& InNewScale);
	virtual void SetPosition(const XMFLOAT3& InNewPosition);
protected:
	virtual void OnMouseMove(int X, int Y);
	virtual void OnLeftMouseButtonDown(int X, int Y);
	virtual void OnLeftMouseButtonUp(int X, int Y);
	virtual void OnCaptureKeyboardInfor(const RInputKey& InKey);

protected:
	float GetSymbol(float InValueOffset, bool bFlip = false);
	float GetSymbolByCubeIndex(float InValueOffset);
	float GetSymbolMaterialByCubeIndex(float InValueOffset);

	//辅助内容 非课程内容
protected:
	float GetAngleRatio(float InAngle);
	void PrintAix(ESelectAxisType InAxisType);

protected:
	float LastT2Value;
	float RotatorRatio;
	int Sample8CubeIndex;
};
