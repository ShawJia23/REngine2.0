#include"Camera.h"
#include"../Component/RComponentMinimal.h"
#include"../Collision/CollisionSystem.h"
#include"../RayCast/RayCastSystem.h"
#include"../Render/Pipeline/RenderLayer/RenderLayerManage.h"
#include"../../Editor/OperationHandle/OperationHandleManage.h"
#include"../../Engine/Construction/MacroConstruction.h"
extern RMeshComponent* SelectAxisComponent;
extern GActorObject* SelectedObject;
RCamera::RCamera():Super()
{
	BUILD_OBJECT_PARAMETERS(this);
	m_rInputComponent = CreateObject<RInputComponent>(inObjectParam,new RInputComponent());

	Radius = 10.f;
	A = XM_PI;
	B = XM_PI;

	m_cameraType = CameraType::CameraRoaming;

	m_mouseSensitivity = 0.25f;
	m_KeyBoardSensitivity = 0.5f;
	m_moveDistance = 2;
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

void RCamera::BuildViewMatrix(GameTimer& gt)
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

void RCamera::Tick(GameTimer& gt)
{
	Super::Tick(gt);
}

void RCamera::ExecuteKeyboard(const RInputKey& inputKey)
{
	if (inputKey.KeyName == "W")
	{
		MoveForward(1.f* m_moveDistance);
	}
	else if (inputKey.KeyName == "S")
	{
		MoveForward(-1.f* m_moveDistance);
	}
	else if (inputKey.KeyName == "A")
	{
		MoveRight(-1.f * m_moveDistance);
	}
	else if (inputKey.KeyName == "D")
	{
		MoveRight(1.f * m_moveDistance);
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
	if (!OperationHandleManage::Get()->IsCaptureMouseNotOnUI())
		return;

	if (SelectAxisComponent)
		return;

	CollisionResult collisionResult;
	RayCastSystem::HitResultByScreen(GetWorld(), X, Y, collisionResult);

	std::shared_ptr<RenderLayerManage> layer = RMeshManage::getInstance().GetDX12Pipeline()->GetGeometryMap().GetRenderLayerManage();
	if (layer && collisionResult.bHit)
	{
		layer->HighlightDisplayObject(collisionResult.RenderData);
		//����ѡ�����
		OperationHandleManage::Get()->SetNewSelectedObject(collisionResult.Actor);

		//��ʾ�����ֱ�
		OperationHandleManage::Get()->DisplaySelectedOperationHandle();
	}
	else
	{
		layer->Clear(EMeshRenderLayerType::RENDERLAYER_SELECT);

		//����ѡ�����
		OperationHandleManage::Get()->SetNewSelectedObject(nullptr);

		//��ʾ�����ֱ�
		OperationHandleManage::Get()->HideSelectedOperationHandle();
	}
}

void RCamera::RotateAroundXAxis(float InRotateDegrees)
{
	//�õ�����ķ���
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//�õ�����Y����ת����
	XMMATRIX RotationX = XMMatrixRotationAxis(XMLoadFloat3(&GetTransformationComponent()->GetRightVector()), InRotateDegrees);

	//�����������Ͱ���Z����ת�������Ч��
	//XMStoreFloat3(&TransformationComponent->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationX));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationX));
}

void RCamera::RotateAroundYAxis(float InRotateDegrees)
{
	//�õ�����ķ���
	XMFLOAT3 RightVector = GetTransformationComponent()->GetRightVector();
	XMFLOAT3 UPVector = GetTransformationComponent()->GetUPVector();
	XMFLOAT3 ForwardVector = GetTransformationComponent()->GetForwardVector();

	//�õ�����Z����ת����
	XMMATRIX RotationY = XMMatrixRotationY(InRotateDegrees);

	//�����������Ͱ���Z����ת�������Ч��
	XMStoreFloat3(&GetTransformationComponent()->GetRightVector(), XMVector3TransformNormal(XMLoadFloat3(&RightVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetUPVector(), XMVector3TransformNormal(XMLoadFloat3(&UPVector), RotationY));
	XMStoreFloat3(&GetTransformationComponent()->GetForwardVector(), XMVector3TransformNormal(XMLoadFloat3(&ForwardVector), RotationY));
}
