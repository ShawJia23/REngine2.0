#include"Camera.h"
#include"../Component/RComponentMinimal.h"
#include"../Collision/CollisionSystem.h"
#include"../RayCast/RayCastSystem.h"
RCamera::RCamera():GActorObject()
{
	CreateObjectParam param;
	param.Outer = this;
	param.Name = "Input";
	m_rInputComponent = CreateObject<RInputComponent>(param,new RInputComponent());

	Radius = 10.f;
	A = XM_PI;
	B = XM_PI;

	m_cameraType = CameraType::CameraRoaming;

	m_mouseSensitivity = 0.25f;
	m_KeyBoardSensitivity = 0.5f;
}

void RCamera::Init()
{
	ViewportInit();

	m_rInputComponent->CaptureKeyboardInforDelegate.Bind(this, &RCamera::ExecuteKeyboard);

	m_rInputComponent->OnRMouseButtonDownDelegate.Bind(this, &RCamera::OnRMouseButtonDown);
	m_rInputComponent->OnRMouseButtonUpDelegate.Bind(this, &RCamera::OnRMouseButtonUp);
	m_rInputComponent->OnLMouseButtonDownDelegate.Bind(this, &RCamera::OnLMouseButtonDown);
	m_rInputComponent->OnLMouseButtonUpDelegate.Bind(this, &RCamera::OnLMouseButtonUp);
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
		//计算和矫正轴
		GetTransformationComponent()->CorrectionVector();

		//算出按自身方向移动意图
		fvector_3d V3;
		GetTransformationComponent()->GetCorrectionPosition(V3);

		//构建Viewmatrix
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

void RCamera::OnRMouseButtonDown(int X, int Y)
{
	bRMouseDown = true;

	LastMousePosition.x = X;
	LastMousePosition.y = Y;

	SetCapture(GetMianWindowsHandle());
}

void RCamera::OnRMouseButtonUp(int X, int Y)
{
	bRMouseDown = false;

	ReleaseCapture();

	LastMousePosition.x = X;
	LastMousePosition.y = Y;
}

void RCamera::OnLMouseButtonDown(int X, int Y)
{
	bLMouseDown = true;
	OnClickedScreen(X, Y);
}

void RCamera::OnLMouseButtonUp(int X, int Y)
{
	bLMouseDown = false;
}


void RCamera::OnMouseMove(int X, int Y)
{
	if (bRMouseDown)
	{
		float XRadians = XMConvertToRadians((float)(X - LastMousePosition.x) * m_mouseSensitivity);
		float YRadians = XMConvertToRadians((float)(Y - LastMousePosition.y) * m_mouseSensitivity);

		switch (m_cameraType)
		{
		case CameraRoaming:
		{
			RotateAroundXAxis(YRadians);
			RotateAroundYAxis(XRadians);
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

		//限制在一定的范围内
		Radius = math_libray::Clamp(Radius, 7.f, 40.f);
	}
}

void RCamera::MoveForward(float InValue)
{
	if (m_cameraType == CameraType::CameraRoaming)
	{
		XMFLOAT3 AT3Position = GetTransformationComponent()->GetPosition();
		XMFLOAT3 AT3ForwardVector = GetTransformationComponent()->GetForwardVector();

		XMVECTOR AmountMovement = XMVectorReplicate(InValue * m_KeyBoardSensitivity);
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

		XMVECTOR AmountMovement = XMVectorReplicate(InValue * m_KeyBoardSensitivity);
		XMVECTOR Right = XMLoadFloat3(&AT3RightVector);
		XMVECTOR Position = XMLoadFloat3(&AT3Position);

		XMStoreFloat3(&AT3Position, XMVectorMultiplyAdd(AmountMovement, Right, Position));
		GetTransformationComponent()->SetPosition(AT3Position);
	}
}

void RCamera::OnClickedScreen(int X, int Y)
{
	CollisionResult collisionResult;
	RayCastSystem::HitResultByScreen(GetWorld(), X, Y, collisionResult);

	std::shared_ptr<RenderLayerManage> layer = GetRenderLayerManage();
	if (layer && collisionResult.bHit)
	{
		layer->HighlightDisplayObject(collisionResult.RenderData);
	}
}

void RCamera::RotateAroundXAxis(float InRotateDegrees)
{
	//拿到相机的方向
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//拿到关于Y的旋转矩阵
	XMMATRIX RotationX = XMMatrixRotationAxis(XMLoadFloat3(&GetTransformationComponent()->GetRightVector()), InRotateDegrees);

	//计算各个方向和按照Z轴旋转后的最终效果
	//XMStoreFloat3(&TransformationComponent->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationX));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationX));
}

void RCamera::RotateAroundYAxis(float InRotateDegrees)
{
	//拿到相机的方向
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//拿到关于Z的旋转矩阵
	XMMATRIX RotationY = XMMatrixRotationY(InRotateDegrees);

	//计算各个方向和按照Z轴旋转后的最终效果
	XMStoreFloat3(&GetTransformationComponent()->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationY));
}
