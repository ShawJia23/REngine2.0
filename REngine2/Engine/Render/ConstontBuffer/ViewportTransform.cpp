#include"ViewportTransform.h"
#include"../../Math/RMath.h"
ViewportTransformation::ViewportTransformation()
    :ViewportPosition(0.f, 0.f, 0.f, 1.f)
    ,ViewProjectionMatrix(RMath::IdentityMatrix4x4())
{

}