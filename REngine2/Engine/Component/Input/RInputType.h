#pragma once

#include "../../EngineMinimal.h"

enum EPressState
{
	Press,//°´ÏÂ
	Release,//ËÉ¿ª
};

struct RInputKey
{
	RInputKey();

	string KeyName;
	EPressState PressState;
};