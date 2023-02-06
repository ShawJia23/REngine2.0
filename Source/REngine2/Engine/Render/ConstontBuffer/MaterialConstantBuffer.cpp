#include "MaterialConstantBuffer.h"

RMaterialConstantBuffer::RMaterialConstantBuffer()
	:BaseColor(0.5f, 0.5f, 0.5f, 1.f)
	,TransformInformation(RMath::IdentityMatrix4x4())
	,MaterialType(0)
	, Roughness(0.2f)
	, BaseColorIndex(-1)
	, NormalIndex(-1)
	, SpecularIndex(-1)
{
}
