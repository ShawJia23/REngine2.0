#include"Camera.h"
#include"../Component/TransformComponent.h"
#include"../Component/InputComponent.h"
RCamera::RCamera()
{
	m_rInputComponent = CreateObject<RInputComponent>(new RInputComponent());
	m_rTransformComponent = CreateObject<RTransformComponent>(new RTransformComponent());
}

void RCamera::Init()
{
	ViewportInit();

	m_rInputComponent->CaptureKeyboardInforDelegate.Bind(this, &RCamera::ExecuteKeyboard);

	m_rInputComponent->OnMouseButtonDownDelegate.Bind(this, &RCamera::OnMouseButtonDown);
	m_rInputComponent->OnMouseButtonUpDelegate.Bind(this, &RCamera::OnMouseButtonUp);
	m_rInputComponent->OnMouseMoveDelegate.Bind(this, &RCamera::OnMouseMove);
	m_rInputComponent->OnMouseWheelDelegate.Bind(this, &RCamera::OnMouseWheel);
}

void RCamera::Tick(float DeltaTime)
{
	
}

void RCamera::ExecuteKeyboard(const RInputKey& inputKey)
{
	if (inputKey.KeyName == "W")
	{
		MoveForward(1.f);
	}
	else if (inputKey.KeyName == "S")
	{
		MoveForward(-1.f);
	}
	else if (inputKey.KeyName == "A")
	{
		MoveRight(-1.f);
	}
	else if (inputKey.KeyName == "D")
	{
		MoveRight(1.f);
	}
	else if (inputKey.KeyName == "Q")
	{
		m_cameraType = CameraType::ObservationObject;
	}
	else  if (inputKey.KeyName == "E")
	{
		m_cameraType = CameraType::CameraRoaming;
	}
}

void RCamera::OnMouseButtonDown(int X, int Y)
{

}

void RCamera::OnMouseButtonUp(int X, int Y)
{
}

void RCamera::OnMouseMove(int X, int Y)
{
}

void RCamera::OnMouseWheel(int X, int Y, float InDelta)
{
}

void RCamera::MoveForward(float InValue)
{
}

void RCamera::MoveRight(float InValue)
{
}

void RCamera::RotateAroundYAxis(float InRotateDegrees)
{
}

void RCamera::RotateAroundZAxis(float InRotateDegrees)
{
}
