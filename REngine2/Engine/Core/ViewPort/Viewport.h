#pragma once
#include"../../Core/Engine.h"

class  RViewport
{
public:
	 RViewport();

	void ViewportInit();
private:
	//���������λ��,UP��Right,Look
	XMFLOAT4X4 ViewMatrix;

	//���ӷ�Χ ���ӽǶ�
	XMFLOAT4X4 ProjectMatrix;
};

