#pragma once
#include "../EngineMinimal.h"
#include <DirectXMath.h>

using namespace DirectX;

namespace RMath
{
    XMFLOAT4X4 IdentityMatrix4x4();

    XMFLOAT3 ToFloat3(const fvector_3d& InV3d);
}