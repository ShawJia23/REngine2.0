#include"RMath.h"
namespace RMath
{
    XMFLOAT4X4 IdentityMatrix4x4()
    {
        return XMFLOAT4X4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    XMFLOAT4 ToFloat4(const fvector_4d& InV4d)
    {
        return XMFLOAT4(InV4d.x, InV4d.y, InV4d.z, InV4d.w);
    }

    XMFLOAT3 ToFloat3(const fvector_3d& InV3d)
    {
        return XMFLOAT3(InV3d.x, InV3d.y, InV3d.z);
    }

    fvector_3d ToVector3d(const XMFLOAT3& InV3d)
    {
        return fvector_3d(InV3d.x, InV3d.y, InV3d.z);
    }

    fmatrix_4x4 ToMatrix4x4(const XMFLOAT4X4& InMatrix4x4)
    {
        return fmatrix_4x4(
            InMatrix4x4._11, InMatrix4x4._12, InMatrix4x4._13, InMatrix4x4._14,
            InMatrix4x4._21, InMatrix4x4._22, InMatrix4x4._23, InMatrix4x4._24,
            InMatrix4x4._31, InMatrix4x4._32, InMatrix4x4._33, InMatrix4x4._34,
            InMatrix4x4._41, InMatrix4x4._42, InMatrix4x4._43, InMatrix4x4._44
        );
    }

    XMFLOAT4X4 ToFloat4x4(const fmatrix_4x4& InMatrix4x4)
    {
        return XMFLOAT4X4(
            InMatrix4x4.m11, InMatrix4x4.m12, InMatrix4x4.m13, InMatrix4x4.m14,
            InMatrix4x4.m21, InMatrix4x4.m22, InMatrix4x4.m23, InMatrix4x4.m24,
            InMatrix4x4.m31, InMatrix4x4.m32, InMatrix4x4.m33, InMatrix4x4.m34,
            InMatrix4x4.m41, InMatrix4x4.m42, InMatrix4x4.m43, InMatrix4x4.m44
        );
    }

    fmatrix_3x3 ToMatrix3x3(const XMFLOAT3X3& InMatrix3x3)
    {
        return fmatrix_3x3(
            InMatrix3x3._11, InMatrix3x3._12, InMatrix3x3._13,
            InMatrix3x3._21, InMatrix3x3._22, InMatrix3x3._23,
            InMatrix3x3._31, InMatrix3x3._32, InMatrix3x3._33);
    }

    XMFLOAT3X3 ToFloat3x3(const fmatrix_3x3& InMatrix3x3)
    {
        return XMFLOAT3X3(
            InMatrix3x3.m11, InMatrix3x3.m12, InMatrix3x3.m13,
            InMatrix3x3.m21, InMatrix3x3.m22, InMatrix3x3.m23,
            InMatrix3x3.m31, InMatrix3x3.m32, InMatrix3x3.m33);
    }

    bool IsAngleRange(float InAngle, float X, float Y)
    {
        if (InAngle >= min(X, Y))
        {
            if (InAngle <= max(X, Y))
            {
                return true;
            }
        }

        return false;
    }

    fvector_3d GetPointSphericalCoordinates(const fvector_3d& InPoint)
    {
        float AnglePre = (180.f / 3.1415926f);

        float R = sqrt(InPoint.x * InPoint.x + InPoint.y * InPoint.y + InPoint.z * InPoint.z);
        float Thata = acos(InPoint.y / R) * AnglePre;
        float Fai = atan2f(InPoint.z, InPoint.x) * AnglePre;

        return fvector_3d(R, Thata, Fai);
    }

    struct FCubeMapAxialRangeR
    {
        FCubeMapAxialRangeR()
            :PositiveX(45.f, 135.f, 45.f, -45.f)//fai ���� 0-45  0--45
            , NegativeX(45.f, 135.f, 135.f, -135.f)//fail ���� 135-180 -135--180
            , PositiveY(0.f, 45.f, 360.f, -360.f)//theta ���� 0-45
            , NegativeY(135.f, 180.f, 360.f, -360.f)//theta ���� 135-180
            , PositiveZ(45.f, 135.f, 45.f, 135.f)
            , NegativeZ(45.f, 135.f, -45.f, -135.f)
        {}

        const fvector_4d PositiveX;
        const fvector_4d NegativeX;

        const fvector_4d PositiveY;
        const fvector_4d NegativeY;

        const fvector_4d PositiveZ;
        const fvector_4d NegativeZ;
    };

    bool IsAngleAxisRange(
        float InAngle,
        float X,
        float Y,
        float InCriticalValue,
        bool bComMin)
    {
        if (bComMin) //��С
        {
            if (InAngle > InCriticalValue)
            {
                if (InAngle <= max(X, Y))
                {
                    return true;
                }
            }
            else if (InAngle < InCriticalValue)
            {
                if (InAngle >= min(X, Y))
                {
                    return true;
                }
            }
            else if (InAngle == 0.f)
            {
                return true;
            }
        }
        else
        {
            if (InAngle > 0.f) //+
            {
                if (InAngle >= max(X, Y))
                {
                    if (InAngle <= InCriticalValue)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (InAngle <= min(X, Y))
                {
                    if (InAngle >= -InCriticalValue)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool IsPointInCubeMapVieport(
        float InPointTheta,
        float InPointFai,
        fvector_4d InCompareValue,
        int bAxisRange = 0,
        float InCriticalValue = 0.f,
        bool bComMin = false)
    {
        if (IsAngleRange(InPointTheta, InCompareValue.x, InCompareValue.y))
        {
            if (bAxisRange == 0)
            {
                if (IsAngleAxisRange(InPointFai, InCompareValue.z, InCompareValue.w, InCriticalValue, bComMin))
                {
                    return true;
                }
            }
            else if (bAxisRange == 1)
            {
                if (InPointFai >= InCompareValue.z)
                {
                    if (InPointFai <= InCompareValue.w)
                    {
                        return true;
                    }
                }
            }
            else if (bAxisRange == 2)
            {
                if (InPointFai <= InCompareValue.z)
                {
                    if (InPointFai >= InCompareValue.w)
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (IsAngleRange(InPointFai, InCompareValue.z, InCompareValue.w))
                {
                    return true;
                }
            }
        }

        return false;
    }

    fquat BuildQuat(const fvector_3d& InForwardVector, const fvector_3d& InUPVector)
    {
        fquat Quat;

        fvector_3d RightVector = fvector_3d::cross_product(InUPVector, InForwardVector);
        RightVector.normalize();

        fvector_3d UPVector = fvector_3d::cross_product(InForwardVector, RightVector);
        UPVector.normalize();

        fmatrix_3x3 RotatorMatrix;
        BuildRotatorMatrix(RotatorMatrix,
            RightVector,
            UPVector,
            InForwardVector);

        math_utils::matrix_to_quat(RotatorMatrix, Quat);

        return Quat;
    }

    frotator BuildRotatorMatrix(const fvector_3d& InForwardVector, const fvector_3d& InUPVector)
    {
        frotator Rotator;

        fvector_3d RightVector = fvector_3d::cross_product(InUPVector, InForwardVector);
        RightVector.normalize();

        fvector_3d UPVector = fvector_3d::cross_product(InForwardVector, RightVector);
        UPVector.normalize();

        fmatrix_3x3 RotatorMatrix;
        BuildRotatorMatrix(RotatorMatrix,
            RightVector,
            UPVector,
            InForwardVector);

        Rotator.inertia_to_object(RotatorMatrix);

        return RMath::ToDXRotator(Rotator);;
    }

    frotator ToDXRotator(const frotator& InRotator)
    {
        return frotator(InRotator.roll, InRotator.pitch, InRotator.yaw);
    }

    void BuildRotatorMatrix(
        fmatrix_3x3& OutMatrix,
        const fvector_3d& InRightVector,
        const fvector_3d& InUPVector,
        const fvector_3d& InForwardVector)
    {
        OutMatrix = {
        InRightVector.x,		InUPVector.x,	InForwardVector.x,
        InRightVector.y,		InUPVector.y,	InForwardVector.y,
        InRightVector.z,		InUPVector.z,	InForwardVector.z };
    }

    void BuildRotatorMatrix(
        fmatrix_3x3& OutMatrix,
        const XMFLOAT3& InRightVector,
        const XMFLOAT3& InUPVector,
        const XMFLOAT3& InForwardVector)
    {
        OutMatrix = {
         InRightVector.x,		InUPVector.x,	InForwardVector.x,
         InRightVector.y,		InUPVector.y,	InForwardVector.y,
         InRightVector.z,		InUPVector.z,	InForwardVector.z };
    }

    void BuildMatrix(
        XMFLOAT4X4& OutMatrix,
        const XMFLOAT3& InPosition,
        const fvector_3d& InScale,
        const XMFLOAT3& InRightVector,
        const XMFLOAT3& InUPVector,
        const XMFLOAT3& InForwardVector)
    {
        OutMatrix = {
      InRightVector.x * InScale.x,		InUPVector.x * InScale.y,	InForwardVector.x * InScale.z,	0.f,
      InRightVector.y * InScale.x,		InUPVector.y * InScale.y,	InForwardVector.y * InScale.z,	0.f,
      InRightVector.z * InScale.x,		InUPVector.z * InScale.y,	InForwardVector.z * InScale.z,	0.f,
      InPosition.x,					    InPosition.y,				InPosition.z,					1.f };
    }

    void BuildInverseMatrix(
        XMMATRIX& OutMatrix,
        const XMFLOAT3& InPosition,
        const fvector_3d& InScale,
        const XMFLOAT3& InRightVector,
        const XMFLOAT3& InUPVector,
        const XMFLOAT3& InForwardVector)
    {
        XMFLOAT4X4 WorldMatrix;
        RMath::BuildMatrix(WorldMatrix,
            InPosition,
            InScale,
            InRightVector,
            InUPVector,
            InForwardVector);

        XMMATRIX WorldMatrixRIX = XMLoadFloat4x4(&WorldMatrix);
        XMVECTOR WorldMatrixRIXDeterminant = XMMatrixDeterminant(WorldMatrixRIX);
        OutMatrix = XMMatrixInverse(&WorldMatrixRIXDeterminant, WorldMatrixRIX);
    }

    bool IsRange(float InMax, int InMin, int InValue)
    {
        return InMin < InValue&& InValue <= InMax;
    }

    int GetSample8CubeIndex(const fvector_3d& InRelativePointPosition)
    {
        fvector_3d Point = GetPointSphericalCoordinates(InRelativePointPosition);

        //��������ֵ
        float PointTheta = Point.y;
        float PointFai = Point.z;

        // Engine_Log("theta=[%f],Fai=[%f]", PointTheta, PointFai);

        if (IsRange(90.f, 0.f, PointTheta))
        {
            if (IsRange(90.f, 0.f, PointFai))
            {
                return 0;
            }
            else if (IsRange(180.f, 90.f, PointFai))
            {
                return 1;
            }
            else if (IsRange(-90.f, -180.f, PointFai))
            {
                return 2;
            }
            else if (IsRange(0.f, -90.f, PointFai))
            {
                return 3;
            }
        }
        else if (IsRange(180.f, 90.f, PointTheta))
        {
            if (IsRange(90.f, 0.f, PointFai))
            {
                return 4;
            }
            else if (IsRange(180.f, 90.f, PointFai))
            {
                return 5;
            }
            else if (IsRange(-90.f, -180.f, PointFai))
            {
                return 6;
            }
            else if (IsRange(0.f, -90.f, PointFai))
            {
                return 7;
            }
        }

        return -1;
    }
}