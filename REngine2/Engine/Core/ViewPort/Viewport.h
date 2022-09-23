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
	//���������λ��,UP��Right,Look
	XMFLOAT4X4 ViewMatrix;

	//���ӷ�Χ ���ӽǶ�
	XMFLOAT4X4 ProjectMatrix;
};

