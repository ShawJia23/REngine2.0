#include"RayCastSystem.h"
#include"../Camera/Camera.h"
#include"../World.h"
#include"../Config/RenderConfig.h"
bool RayCastSystem::GetRayParamByScreen(const fvector_2id& ScreenXY,
	XMVECTOR& OriginPoint,
	XMVECTOR& Direction,
	XMMATRIX& ViewInverseMatrix)
{
	if (RCamera* camera = RWorld::getInstance().GetCamera())
	{
		int H = camera->GetHeight();
		int W = camera->GetWidth();

		fvector_2d View;
		View.x = (2.f * ScreenXY.x / W - 1.f) / camera->GetProjectMatrix()._11;
		View.y = (-2.f * ScreenXY.y / H + 1.f) / camera->GetProjectMatrix()._22;

		//视口下的 原点 和 方向
		OriginPoint = DirectX::XMVectorSet(0.f, 0.f, 0.f, 1.f);
		Direction = DirectX::XMVectorSet(View.x, View.y, 1.f, 0.f);

		auto viewMatrix = camera->GetViewMatrix();
		XMMATRIX ViewMatrix = DirectX::XMLoadFloat4x4(&viewMatrix);
		XMVECTOR ViewMatrixDeterminant = DirectX::XMMatrixDeterminant(ViewMatrix);
		ViewInverseMatrix = DirectX::XMMatrixInverse(&ViewMatrixDeterminant, ViewMatrix);
		return true;
	}

	return false;
}

bool RayCastSystem::HitResultByScreen(int ScreenX, int ScreenY, CollisionResult& OutResult)
{
	XMVECTOR OriginPoint;
	XMVECTOR Direction;
	XMMATRIX ViewInverseMatrix;
	if (GetRayParamByScreen(
		fvector_2id(ScreenX, ScreenY),
		OriginPoint,
		Direction,
		ViewInverseMatrix))
	{
		return CollisionScene::RaycastSingle(OriginPoint, Direction, ViewInverseMatrix, OutResult);
	}

	return false;
}

bool RayCastSystem::HitSpecificObjectsResultByScreen(
	GActorObject* InSpecificObjects,
	const std::vector<RComponent*>& IgnoreComponents,
	int ScreenX, int ScreenY, CollisionResult& OutResult)
{
	XMVECTOR OriginPoint;
	XMVECTOR Direction;
	XMMATRIX ViewInverseMatrix;
	if (GetRayParamByScreen(
		fvector_2id(ScreenX, ScreenY),
		OriginPoint,
		Direction,
		ViewInverseMatrix))
	{
		return CollisionScene::RaycastSingle(
			InSpecificObjects,
			IgnoreComponents,
			OriginPoint, Direction, ViewInverseMatrix, OutResult);
	}
}