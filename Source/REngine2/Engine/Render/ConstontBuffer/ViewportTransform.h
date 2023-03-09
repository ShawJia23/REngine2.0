#pragma once
#include"../../Engine.h"
struct ViewportTransformation
{
	ViewportTransformation();

	XMFLOAT4 ViewportPosition;
	XMFLOAT4X4 ViewProjectionMatrix;

	XMFLOAT4X4 TexViewProjectionMatrix;
};