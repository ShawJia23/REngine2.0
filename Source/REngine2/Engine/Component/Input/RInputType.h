#pragma once

#include "../../EngineMinimal.h"

enum EPressState
{
	Press,//����
	Release,//�ɿ�
};

struct RInputKey
{
	RInputKey();

	string KeyName;
	EPressState PressState;
};