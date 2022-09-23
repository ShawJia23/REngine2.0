#pragma once

#include"ViewPort/Viewport.h"
#include"RObject/RMinimalObject.h"
#include"CameraType.h"

struct RInputKey;
class RTransformComponent;
class RInputComponent;


class RCamera :public RMinimalObject, public RViewport 
{
	RVARIABLE()
	RTransformComponent* m_rTransformComponent;

	RVARIABLE()
	RInputComponent* m_rInputComponent;
public:
	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void ExecuteKeyboard(const RInputKey& inputKey);

	virtual void BuildViewMatrix(float DeltaTime);

	virtual void OnMouseButtonDown(int X, int Y);
	virtual void OnMouseButtonUp(int X, int Y);
	virtual void OnMouseMove(int X, int Y);
	virtual void OnMouseWheel(int X, int Y, float InDelta);

	virtual void MoveForward(float InValue);
	virtual void MoveRight(float InValue);
protected:
	void RotateAroundYAxis(float InRotateDegrees);
	void RotateAroundZAxis(float InRotateDegrees);

	CameraType m_cameraType;

	//ÇòÃæ×ø±ê
	float Radius;
	float A;//Theta
	float B;//
public:
	RCamera();

	FORCEINLINE RTransformComponent* GetTransformComponent() { return m_rTransformComponent; }
	FORCEINLINE RInputComponent* GetInputComponent() { return m_rInputComponent; }
};