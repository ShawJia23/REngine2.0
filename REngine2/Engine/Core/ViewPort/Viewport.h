#pragma once
#include"../../Core/Engine.h"

class  RViewport
{
public:
	 RViewport();

	void ViewportInit();

	void SetViewMatrix(const XMMATRIX& viewMatrix) { XMStoreFloat4x4(&ViewMatrix, viewMatrix); }

	void SetProjectMatrix(const XMMATRIX& projectMatrix) { XMStoreFloat4x4(&ProjectMatrix, projectMatrix); }
	
	XMFLOAT4X4 GetViewMatrix() { return ViewMatrix; }

	XMFLOAT4X4 GetProjectMatrix() { return ProjectMatrix; }
private:
	//定义摄像机位置,UP，Right,Look
	XMFLOAT4X4 ViewMatrix;

	//可视范围 可视角度
	XMFLOAT4X4 ProjectMatrix;
};

