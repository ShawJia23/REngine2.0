#pragma once
#include"../Engine.h"
struct ViewportInfo
{
	XMFLOAT4 ViewportPosition;
	//定义摄像机位置,UP，Right,Look
	XMFLOAT4X4 ViewMatrix;

	//可视范围 可视角度
	XMFLOAT4X4 ProjectMatrix;
};