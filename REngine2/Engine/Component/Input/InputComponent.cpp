#include"InputComponent.h"
#include"Input.h"

void RInputComponent::Init()
{
	RMouseDownDelegate.AddFunction(this, &RInputComponent::OnRMouseButtonDown);
	RMouseUpDelegate.AddFunction(this, &RInputComponent::OnRMouseButtonUp);
	LMouseDownDelegate.AddFunction(this, &RInputComponent::OnLMouseButtonDown);
	LMouseUpDelegate.AddFunction(this, &RInputComponent::OnLMouseButtonUp);
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

void RInputComponent::OnRMouseButtonDown(int X, int Y)
{
	if (OnRMouseButtonDownDelegate.IsBound())
	{
		OnRMouseButtonDownDelegate.Execute((int)X, (int)Y);
	}
}

void RInputComponent::OnRMouseButtonUp(int X, int Y)
{
	if (OnRMouseButtonUpDelegate.IsBound())
	{
		OnRMouseButtonUpDelegate.Execute((int)X, (int)Y);
	}
}


void RInputComponent::OnLMouseButtonDown(int X, int Y)
{
	if (OnLMouseButtonDownDelegate.IsBound())
	{
		OnLMouseButtonDownDelegate.Execute((int)X, (int)Y);
	}
}

void RInputComponent::OnLMouseButtonUp(int X, int Y)
{
	if (OnLMouseButtonUpDelegate.IsBound())
	{
		OnLMouseButtonUpDelegate.Execute((int)X, (int)Y);
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
