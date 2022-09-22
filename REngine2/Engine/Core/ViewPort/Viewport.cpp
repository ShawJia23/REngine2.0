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
    //������Ұ��������͸��ͶӰ����
    XMMATRIX Project = XMMatrixPerspectiveFovLH(
        0.25f * XM_PI, //�Ի���Ϊ��λ�����϶��µ��ӳ��ǡ�
        AspectRatio,//��ͼ�ռ� X:Y ���ݺ�ȡ�
        1.0f,//��������ƽ��ľ��롣��������㡣
        1000.f//��Զ����ƽ��ľ��롣��������㡣
    );

    XMStoreFloat4x4(&ProjectMatrix, Project);
}
