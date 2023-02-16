#include "Viewport.h"
#include"../Math/RMath.h"
#include"../Config/RenderConfig.h"
RViewport::RViewport()
    :ViewMatrix(RMath::IdentityMatrix4x4())
    , ProjectMatrix(RMath::IdentityMatrix4x4())
{

}

void RViewport::ViewportInit()
{
    float AspectRatio = (float)EngineRenderConfig::GetRenderConfig()->ScreenWidth 
        / (float)EngineRenderConfig::GetRenderConfig()->ScreenHeight;
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


void RViewport::OnResetSize(int width, int height)
{
    float AspectRatio = (float)width
        / (float)height;
    //(1,1,0) (-1,1,0) (-1,-1,0) (1,-1,0) (1,1,1) (-1,1,1) (-1,-1,1) (1,-1,1)
    //������Ұ��������͸��ͶӰ����
    XMMATRIX Project = XMMatrixPerspectiveFovLH(
        0.25f * XM_PI, //�Ի���Ϊ��λ�����϶��µ��ӳ��ǡ�
        AspectRatio,//��ͼ�ռ� X:Y ���ݺ�ȡ�
        1.0f,//��������ƽ��ľ��롣��������㡣
        1000.f//��Զ����ƽ��ľ��롣��������㡣
    );

    XMStoreFloat4x4(&ProjectMatrix, Project);

    ViewprotInfo =
    {
        0.0f,//TopLeftX
        0.0f,//TopLeftY
        (float)width,//Width
        (float)height,//Height
        0.0f,//MinDepth
        1.0f //MaxDepth
    };
    ViewprotRect =
    {
        0,//left
        0,//top
        (LONG)width,//right
        (LONG)height//bottom
    };
}