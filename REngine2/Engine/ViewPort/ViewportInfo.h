#pragma once
#include"../Engine.h"
struct ViewportInfo
{
	XMFLOAT4 ViewportPosition;
	//���������λ��,UP��Right,Look
	XMFLOAT4X4 ViewMatrix;

	//���ӷ�Χ ���ӽǶ�
	XMFLOAT4X4 ProjectMatrix;
};