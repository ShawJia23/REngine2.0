#pragma once
#include "OperationHandleBase.h"
#include "ScalingArrow.CodeReflection.h"
class RScalingArrow :public OperationHandleBase
{
	CODEREFLECTION()

public:
	RScalingArrow();

	void CreateMesh();

protected:
	virtual fvector_3d AnyAxis(
		const fvector_3d& InRayWorldOriginPoint,
		const fvector_3d& InRayWorldDirection,
		const fvector_3d& InActorWorldOriginPoint);

protected:
	virtual void OnMouseMove(int X, int Y);
	virtual void OnLeftMouseButtonDown(int X, int Y);
	virtual void OnLeftMouseButtonUp(int X, int Y);
	virtual void OnCaptureKeyboardInfor(const RInputKey& InKey);

protected:
	float LastT2Value;
};