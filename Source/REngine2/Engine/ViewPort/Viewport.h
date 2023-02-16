#pragma once
#include"../Engine.h"

class  RViewport
{
public:
	 RViewport();

	void ViewportInit();

	virtual void OnResetSize(int width, int height);

	void SetViewMatrix(const XMMATRIX& viewMatrix) { XMStoreFloat4x4(&ViewMatrix, viewMatrix); }

	void SetProjectMatrix(const XMMATRIX& projectMatrix) { XMStoreFloat4x4(&ProjectMatrix, projectMatrix); }
	
	XMFLOAT4X4 GetViewMatrix() { return ViewMatrix; }

	XMFLOAT4X4 GetProjectMatrix() { return ProjectMatrix; }
protected:
	//和屏幕的视口有关
	D3D12_VIEWPORT ViewprotInfo;
	D3D12_RECT ViewprotRect;

	//定义摄像机位置,UP，Right,Look
	XMFLOAT4X4 ViewMatrix;

	//可视范围 可视角度
	XMFLOAT4X4 ProjectMatrix;
};

