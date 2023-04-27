#pragma once

#include"../ViewPort/ClientViewport.h"
#include"RObject/RMinimalObject.h"
#include"CameraType.h"
#include"../Actor/ActorObject.h"
#include "Camera.CodeReflection.h"
struct RInputKey;
class RInputComponent;

class RCamera :public ClientViewport
{
	CODEREFLECTION()

	RVARIABLE()
	RInputComponent* m_rInputComponent;
public:
	RCamera();
	FORCEINLINE RInputComponent* GetInputComponent() { return m_rInputComponent; }
public:
	virtual void Init();
	virtual void Tick(GameTimer& gt);
	virtual void BuildViewMatrix(GameTimer& gt);

protected:
	virtual void ExecuteKeyboard(const RInputKey& inputKey);

	virtual void OnRMouseButtonDown(int X, int Y);
	virtual void OnRMouseButtonUp(int X, int Y);
	virtual void OnLMouseButtonDown(int X, int Y);
	virtual void OnLMouseButtonUp(int X, int Y);
	virtual void OnMouseMove(int X, int Y);
	virtual void OnMouseWheel(int X, int Y, float InDelta);

public:
	virtual void MoveForward(float InValue);
	virtual void MoveRight(float InValue);
	virtual void OnClickedScreen(int X, int Y);
protected:
	void RotateAroundXAxis(float InRotateDegrees);
	void RotateAroundYAxis(float InRotateDegrees);

	POINT LastMousePosition;
	bool bRMouseDown;
	bool bLMouseDown;
	float m_mouseSensitivity;
	float m_KeyBoardSensitivity;
	float m_moveDistance;
	CameraType m_cameraType;

	//ÇòÃæ×ø±ê
	float Radius;
	float A;//Theta
	float B;//

};