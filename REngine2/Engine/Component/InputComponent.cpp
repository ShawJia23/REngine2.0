#include"InputComponent.h"
#include"Input/Input.h"

void RInputComponent::Init()
{
	MouseDownDelegate.AddFunction(this, &RInputComponent::OnMouseButtonDown);
	MouseUpDelegate.AddFunction(this, &RInputComponent::OnMouseButtonUp);
	MouseMoveDelegate.AddFunction(this, &RInputComponent::OnMouseMove);
	MousesWheelsDelegate.AddFunction(this, &RInputComponent::OnMouseWheel);
}

void RInputComponent::Tick(float DeltaTime)
{
	if (CaptureKeyboardInforDelegate.IsBound())
	{
		RInputKey pInputKey;
		if (GetAsyncKeyState('W') & 0x8000)
		{
			pInputKey.KeyName = "W";
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			pInputKey.KeyName = "S";
		}
		else if (GetAsyncKeyState('A') & 0x8000)
		{
			pInputKey.KeyName = "A";
		}
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			pInputKey.KeyName = "D";
		}
		else if (GetAsyncKeyState('Q') & 0x8000)
		{
			pInputKey.KeyName = "Q";
		}
		else if (GetAsyncKeyState('E') & 0x8000)
		{
			pInputKey.KeyName = "E";
		}
		else
		{
			return;
		}
		CaptureKeyboardInforDelegate.Execute(pInputKey);
	}
}


void RInputComponent::OnMouseButtonDown(int X, int Y)
{
	if (OnMouseButtonDownDelegate.IsBound())
	{
		OnMouseButtonDownDelegate.Execute((int)X, (int)Y);
	}
}

void RInputComponent::OnMouseButtonUp(int X, int Y)
{
	if (OnMouseButtonUpDelegate.IsBound())
	{
		OnMouseButtonUpDelegate.Execute((int)X, (int)Y);
	}
}

void RInputComponent::OnMouseMove(int X, int Y)
{
	if (OnMouseMoveDelegate.IsBound())
	{
		OnMouseMoveDelegate.Execute((int)X, (int)Y);
	}
}

void RInputComponent::OnMouseWheel(int X, int Y, float InDelta)
{
	if (OnMouseWheelDelegate.IsBound())
	{
		OnMouseWheelDelegate.Execute((int)X, (int)Y, (float)InDelta);
	}
}
