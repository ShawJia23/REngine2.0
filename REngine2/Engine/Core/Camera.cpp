#include"Camera.h"
#include"../Component/TransformComponent.h"
#include"../Component/InputComponent.h"
RCamera::RCamera():GActorObject()
{
	m_rInputComponent = CreateObject<RInputComponent>(new RInputComponent());

	Radius = 10.f;
	A = XM_PI;
	B = XM_PI;

	m_cameraType = CameraType::CameraRoaming;

	m_mouseSensitivity = 0.05f;
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
	BuildViewMatrix(DeltaTime);
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

void RCamera::BuildViewMatrix(float DeltaTime)
{
	switch (m_cameraType)
	{
	case CameraRoaming:
	{
		//����ͽ�����
		GetTransformationComponent()->CorrectionVector();

		//������������ƶ���ͼ
		fvector_3d V3;
		GetTransformationComponent()->GetCorrectionPosition(V3);

		//����Viewmatrix
		XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
		XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
		XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

		SetViewMatrix({
			RightVector.x,	UPVector.x,	ForwardVector.x,	0.f,
			RightVector.y,	UPVector.y,	ForwardVector.y,	0.f,
			RightVector.z,	UPVector.z,	ForwardVector.z,	0.f,
			V3.x,			V3.y,		V3.z,				1.f });

		break;
	}
	case ObservationObject:
	{
		XMFLOAT3& CameraPos = GetTransformationComponent()->GetPosition();

		CameraPos.x = Radius * sinf(B) * cosf(A);
		CameraPos.z = Radius * sinf(B) * sinf(A);
		CameraPos.y = Radius * cosf(B);

		XMVECTOR Pos = XMVectorSet(CameraPos.x, CameraPos.y, CameraPos.z, 1.0f);
		XMVECTOR ViewTarget = XMVectorZero();
		XMVECTOR ViewUp = XMVectorSet(0.f, 1.0f, 0.f, 0.f);

		XMMATRIX ViewLookAt = XMMatrixLookAtLH(Pos, ViewTarget, ViewUp);
		SetViewMatrix(ViewLookAt);

		break;
	}
	}
}

void RCamera::OnMouseButtonDown(int X, int Y)
{
	bLeftMouseDown = true;

	LastMousePosition.x = X;
	LastMousePosition.y = Y;

	SetCapture(GetMianWindowsHandle());
}

void RCamera::OnMouseButtonUp(int X, int Y)
{
	bLeftMouseDown = false;

	ReleaseCapture();

	LastMousePosition.x = X;
	LastMousePosition.y = Y;
}

void RCamera::OnMouseMove(int X, int Y)
{
	if (bLeftMouseDown)
	{
		float XRadians = XMConvertToRadians((float)(X - LastMousePosition.x) * m_mouseSensitivity);
		float YRadians = XMConvertToRadians((float)(Y - LastMousePosition.y) * m_mouseSensitivity);

		switch (m_cameraType)
		{
		case CameraRoaming:
		{
			RotateAroundYAxis(YRadians);
			RotateAroundZAxis(XRadians);
			break;
		}
		case ObservationObject:
		{
			A += (-XRadians);
			B += YRadians;

			A = math_libray::Clamp(A, 0.f, XM_2PI * 2.f);
			break;
		}
		}
	}

	LastMousePosition.x = X;
	LastMousePosition.y = Y;
}

void RCamera::OnMouseWheel(int X, int Y, float InDelta)
{
	if (m_cameraType == ObservationObject)
	{
		Radius += (InDelta / 100.f);

		//������һ���ķ�Χ��
		Radius = math_libray::Clamp(Radius, 7.f, 40.f);
	}
}

void RCamera::MoveForward(float InValue)
{
	if (m_cameraType == CameraType::CameraRoaming)
	{
		XMFLOAT3 AT3Position = GetTransformationComponent()->GetPosition();
		XMFLOAT3 AT3ForwardVector = GetTransformationComponent()->GetForwardVector();

		XMVECTOR AmountMovement = XMVectorReplicate(InValue * 1.f);
		XMVECTOR Forward = XMLoadFloat3(&AT3ForwardVector);
		XMVECTOR Position = XMLoadFloat3(&AT3Position);
		
		XMStoreFloat3(&AT3Position, XMVectorMultiplyAdd(AmountMovement, Forward, Position));
		GetTransformationComponent()->SetPosition(AT3Position);
	}
}

void RCamera::MoveRight(float InValue)
{
	if (m_cameraType == CameraType::CameraRoaming)
	{
		XMFLOAT3 AT3Position = GetTransformationComponent()->GetPosition();
		XMFLOAT3 AT3RightVector = GetTransformationComponent()->GetRightVector();

		XMVECTOR AmountMovement = XMVectorReplicate(InValue * 1.f);
		XMVECTOR Right = XMLoadFloat3(&AT3RightVector);
		XMVECTOR Position = XMLoadFloat3(&AT3Position);

		XMStoreFloat3(&AT3Position, XMVectorMultiplyAdd(AmountMovement, Right, Position));
		GetTransformationComponent()->SetPosition(AT3Position);
	}
}

void RCamera::RotateAroundYAxis(float InRotateDegrees)
{
	//�õ�����ķ���
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//�õ�����Y����ת����
	XMMATRIX RotationY = XMMatrixRotationAxis(XMLoadFloat3(&GetTransformationComponent()->GetRightVector()), InRotateDegrees);

	//�����������Ͱ���Z����ת�������Ч��
	//XMStoreFloat3(&TransformationComponent->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationY));
}

void RCamera::RotateAroundZAxis(float InRotateDegrees)
{
	//�õ�����ķ���
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//�õ�����Z����ת����
	XMMATRIX RotationZ = XMMatrixRotationZ(InRotateDegrees);

	//�����������Ͱ���Z����ת�������Ч��
	XMStoreFloat3(&GetTransformationComponent()->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationZ));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationZ));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationZ));
}
