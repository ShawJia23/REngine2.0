#include"RayCastSystem.h"
#include"../Camera/Camera.h"
#include"../Core/World.h"
#include"../Config/RenderConfig.h"
bool RayCastSystem::HitResultByScreen(RWorld* inWorld, int screenX, int screenY, CollisionResult& outResult)
{
	if (RCamera* camera = inWorld->GetCamera())
	{
		int H = EngineRenderConfig::GetRenderConfig()->ScreenHeight;
		int W = EngineRenderConfig::GetRenderConfig()->ScreenWidth;

		fvector_2d View;
		View.x = (2.f * screenX / W - 1.f) / camera->GetProjectMatrix()._11;
		View.y = (-2.f * screenY / H + 1.f) / camera->GetProjectMatrix()._22;

		//视口下的 原点 和 方向
		XMVECTOR OriginPoint = XMVectorSet(0.f, 0.f, 0.f, 1.f);
		XMVECTOR Direction = XMVectorSet(View.x, View.y, 1.f, 0.f);

		XMMATRIX ViewMatrix = XMLoadFloat4x4(&camera->GetViewMatrix());
		XMVECTOR ViewMatrixDeterminant = XMMatrixDeterminant(ViewMatrix);
		XMMATRIX ViewInverseMatrix = XMMatrixInverse(&ViewMatrixDeterminant, ViewMatrix);

		CollisionScene::RaycastSingle(inWorld, OriginPoint, Direction, ViewInverseMatrix, outResult);
	}

	return false;
}