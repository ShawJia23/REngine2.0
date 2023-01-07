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
		XMVECTOR OriginPoint = DirectX::XMVectorSet(0.f, 0.f, 0.f, 1.f);
		XMVECTOR Direction = DirectX::XMVectorSet(View.x, View.y, 1.f, 0.f);

		auto viewMatrix = camera->GetViewMatrix();
		XMMATRIX ViewMatrix = DirectX::XMLoadFloat4x4(&viewMatrix);
		XMVECTOR ViewMatrixDeterminant = DirectX::XMMatrixDeterminant(ViewMatrix);
		XMMATRIX ViewInverseMatrix = DirectX::XMMatrixInverse(&ViewMatrixDeterminant, ViewMatrix);

		CollisionScene::RaycastSingle(inWorld, OriginPoint, Direction, ViewInverseMatrix, outResult);
	}

	return false;
}