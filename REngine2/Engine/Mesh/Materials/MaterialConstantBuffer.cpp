#include "MaterialConstantBuffer.h"
#include"../../Math/RMath.h"

RMaterialConstantBuffer::RMaterialConstantBuffer()
	:BaseColor(0.5f, 0.5f, 0.5f, 1.f)
	,TransformInformation(RMath::IdentityMatrix4x4())
	,MaterialType(0)
	, Roughness(0.2f)
{
}
