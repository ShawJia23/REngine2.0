#include "MaterialConstantBuffer.h"
#include"../../Math/RMath.h"

RMaterialConstantBuffer::RMaterialConstantBuffer()
	:TransformInformation(RMath::IdentityMatrix4x4())
{
}
