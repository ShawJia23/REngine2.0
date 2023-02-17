#pragma once
#include "../EngineMinimal.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace RMath
{
    XMFLOAT4X4 IdentityMatrix4x4();

	XMFLOAT4 ToFloat4(const fvector_4d& InV4d);
	XMFLOAT3 ToFloat3(const fvector_3d& InV3d);
	fvector_3d ToVector3d(const XMFLOAT3& InV3d);

	fmatrix_4x4 ToMatrix4x4(const XMFLOAT4X4& InMatrix4x4);
	XMFLOAT4X4 ToFloat4x4(const fmatrix_4x4& InMatrix4x4);

	fmatrix_3x3 ToMatrix3x3(const XMFLOAT3X3& InMatrix3x3);
	XMFLOAT3X3 ToFloat3x3(const fmatrix_3x3& InMatrix3x3);

	bool IsAngleRange(float InAngle, float X, float Y);
	fvector_3d GetPointSphericalCoordinates(const fvector_3d& InPoint);

	fquat BuildQuat(const fvector_3d& InForwardVector, const fvector_3d& InUPVector = fvector_3d(0.f, 1.f, 0.f));

	frotator BuildRotatorMatrix(const fvector_3d& InForwardVector, const fvector_3d& InUPVector = fvector_3d(0.f, 1.f, 0.f));

	frotator ToDXRotator(const frotator& InRotator);

	void BuildRotatorMatrix(
		fmatrix_3x3& OutMatrix,
		const XMFLOAT3& InRightVector,
		const XMFLOAT3& InUPVector,
		const XMFLOAT3& InForwardVector);

	void BuildRotatorMatrix(
		fmatrix_3x3& OutMatrix,
		const fvector_3d& InRightVector,
		const fvector_3d& InUPVector,
		const fvector_3d& InForwardVector);

	void BuildMatrix(
		XMFLOAT4X4& OutMatrix,
		const XMFLOAT3& InPosition,
		const fvector_3d& InScale,
		const XMFLOAT3& InRightVector, const XMFLOAT3& InUPVector, const XMFLOAT3& InForwardVector);

	void BuildInverseMatrix(
		XMMATRIX& OutMatrix,
		const XMFLOAT3& InPosition,
		const fvector_3d& InScale,
		const XMFLOAT3& InRightVector, const XMFLOAT3& InUPVector, const XMFLOAT3& InForwardVector);

	int GetSample8CubeIndex(const fvector_3d& InRelativePointPosition);

	//²åÖµ
	template<class T>
	static T Lerp(const T& InA, const T& InB, float InTime)
	{
		return InA + (InB - InA) * InTime;
	}
}