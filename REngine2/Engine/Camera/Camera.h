#pragma once

#include"../Core/ViewPort/Viewport.h"
#include"../Core/RObject/RMinimalObject.h"
#include"CameraType.h"
#include"../Interface/DXDeviceInterface.h"
#include"../Actor/ActorObject.h"
struct RInputKey;
class RInputComponent;

class RCamera :public GActorObject, public RViewport ,public IDirectXDeviceInterface
{
	RVARIABLE()
	RInputComponent* m_rInputComponent;
public:
	RCamera();
	FORCEINLINE RInputComponent* GetInputComponent() { return m_rInputComponent; }
public:
	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void ExecuteKeyboard(const RInputKey& inputKey);

	virtual void BuildViewMatrix(float DeltaTime);

	virtual void OnRMouseButtonDown(int X, int Y);
	virtual void OnRMouseButtonUp(int X, int Y);
	virtual void OnLMouseButtonDown(int X, int Y);
	virtual void OnLMouseButtonUp(int X, int Y);
	virtual void OnMouseMove(int X, int Y);
	virtual void OnMouseWheel(int X, int Y, float InDelta);

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
	CameraType m_cameraType;

	//ÇòÃæ×ø±ê
	float Radius;
	float A;//Theta
	float B;//

};