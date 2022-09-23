#pragma once
#include"../../Core/Engine.h"
struct ViewportTransformation
{
	ViewportTransformation();

	XMFLOAT4X4 ViewProjectionMatrix;
};