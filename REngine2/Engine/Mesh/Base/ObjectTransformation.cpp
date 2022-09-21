#include "ObjectTransformation.h"

RObjectTransformation::RObjectTransformation()
    :World(RObjectTransformation::IdentityMatrix4x4())
{
}

XMFLOAT4X4 RObjectTransformation::IdentityMatrix4x4()
{
    return XMFLOAT4X4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}