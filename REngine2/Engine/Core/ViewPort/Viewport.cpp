#include "Viewport.h"
#include"../../Math/RMath.h"
#include"../../Config/RenderConfig.h"
RViewport::RViewport()
    :ViewMatrix(RMath::IdentityMatrix4x4())
    , ProjectMatrix(RMath::IdentityMatrix4x4())
{

}

void RViewport::ViewportInit()
{
    float AspectRatio = (float)EngineRenderConfig::GetRenderConfig()->ScrrenWidth / (float)EngineRenderConfig::GetRenderConfig()->ScrrenHight;
    //(1,1,0) (-1,1,0) (-1,-1,0) (1,-1,0) (1,1,1) (-1,1,1) (-1,-1,1) (1,-1,1)
    //基于视野构建左手透视投影矩阵
    XMMATRIX Project = XMMatrixPerspectiveFovLH(
        0.25f * XM_PI, //以弧度为单位的自上而下的视场角。
        AspectRatio,//视图空间 X:Y 的纵横比。
        1.0f,//到近剪裁平面的距离。必须大于零。
        1000.f//到远剪裁平面的距离。必须大于零。
    );

    XMStoreFloat4x4(&ProjectMatrix, Project);
}
