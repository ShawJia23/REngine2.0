#include "ClientViewport.h"
#include "../Component/TransformComponent/TransformComponent.h"
#include"../Math/RMath.h"

ClientViewport::ClientViewport()
    :SuperV()
    , SuperA()
    , bDirty(true)
{
}

void ClientViewport::SetFrustum(float InYFOV, float InZNear, float InZFar)
{
    SetFrustum(InYFOV, ViewportData.Aspect, InZNear, InZFar);
}

void ClientViewport::SetFrustum(float InYFOV, float InAspect, float InZNear, float InZFar)
{
    ViewportData.YFOV = InYFOV;
    ViewportData.Aspect = InAspect;
    ViewportData.ZNear = InZNear;
    ViewportData.ZFar = InZFar;

#if USE_SIMPLE_LIB_MATH
    ProjectMatrix = EngineMath::ToFloat4x4(math_utils::matrix_perspective(
        InYFOV, //�Ի���Ϊ��λ�����϶��µ��ӳ��ǡ�
        InAspect,//��ͼ�ռ� X:Y ���ݺ�ȡ�
        InZNear,//��������ƽ��ľ��롣��������㡣
        InZFar//��Զ����ƽ��ľ��롣��������㡣
    ));
#else
    //������Ұ��������͸��ͶӰ����
    XMMATRIX Project = XMMatrixPerspectiveFovLH(
        InYFOV, //�Ի���Ϊ��λ�����϶��µ��ӳ��ǡ�
        InAspect,//��ͼ�ռ� X:Y ���ݺ�ȡ�
        InZNear,//��������ƽ��ľ��롣��������㡣
        InZFar//��Զ����ƽ��ľ��롣��������㡣
    );

    XMStoreFloat4x4(&ProjectMatrix, Project);

    BoundingFrustum::CreateFromMatrix(m_Frustum,Project);
#endif // USE_SIMPLE_LIB_MATH
    SetDirty(true);
}

void ClientViewport::FaceTarget(
    const fvector_3d& InPosition,
    const fvector_3d& InTargetPosition,
    const fvector_3d& InUP)
{
    //�õ���������
    fvector_3d TmpFaceVector = InTargetPosition - InPosition;
    TmpFaceVector.normalize();

    fvector_3d TmpRightVector = fvector_3d::cross_product(InUP, TmpFaceVector);
    TmpRightVector.normalize();

    fvector_3d TmpUPVector = fvector_3d::cross_product(TmpFaceVector, TmpRightVector);
    TmpUPVector.normalize();

    //ת��
    XMFLOAT3 XMFaceVector = RMath::ToFloat3(TmpFaceVector);
    XMFLOAT3 XMRightVector = RMath::ToFloat3(TmpRightVector);
    XMFLOAT3 XMUPVector = RMath::ToFloat3(TmpUPVector);

    //��ֵ����
    GetForwardVector() = XMFaceVector;
    GetRightVector() = XMRightVector;
    GetUPVector() = XMUPVector;

    SetDirty(true);
}

void ClientViewport::Tick(GameTimer& gt)
{
    BuildViewMatrix(gt);
}

void ClientViewport::BuildViewMatrix(GameTimer& gt)
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

    ViewMatrix = {
        RightVector.x,	UPVector.x,	ForwardVector.x,	0.f,
        RightVector.y,	UPVector.y,	ForwardVector.y,	0.f,
        RightVector.z,	UPVector.z,	ForwardVector.z,	0.f,
        V3.x,			V3.y,		V3.z,				1.f };
}

void ClientViewport::OnResetSize(int InWidth, int InHeight)
{
    SuperV::OnResetSize(InWidth, InHeight);

    ViewportData.ResetSize(InWidth, InHeight);
}

void ClientViewport::BuildOrthographicOffCenterLHMatrix(float InRadius, const fvector_3d& InTargetPosition)
{
    XMFLOAT3 TargetPosition = RMath::ToFloat3(InTargetPosition);
    XMVECTOR TargetPositionTOR = XMLoadFloat3(&TargetPosition);

    XMMATRIX ShadowViewMatrixRTX = XMLoadFloat4x4(&ViewMatrix);

    //�任���ƹ��ӿڿռ�
    XMFLOAT3 ViewCenter;
    XMStoreFloat3(&ViewCenter, XMVector3TransformCoord(TargetPositionTOR, ShadowViewMatrixRTX));

    //������ϵ
    float ViewLeft = ViewCenter.x - InRadius;
    float ViewRight = ViewCenter.x + InRadius;
    float ViewBottom = ViewCenter.y - InRadius;
    float ViewTop = ViewCenter.y + InRadius;
    float NearZ = ViewCenter.z - InRadius;
    float FarZ = ViewCenter.z + InRadius;

    XMMATRIX ProjectMatrixRIX = XMMatrixOrthographicOffCenterLH(
        ViewLeft,
        ViewRight,
        ViewBottom,
        ViewTop,
        NearZ,
        FarZ);

    //�洢
    XMStoreFloat4x4(&ProjectMatrix, ProjectMatrixRIX);
}