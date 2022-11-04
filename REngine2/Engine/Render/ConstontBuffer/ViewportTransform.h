#pragma once
#include"../../Core/Engine.h"
struct ViewportTransformation
{
	ViewportTransformation();

	XMFLOAT4 ViewportPosition;
	XMFLOAT4X4 ViewProjectionMatrix;
};