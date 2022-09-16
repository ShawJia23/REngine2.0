#pragma once
#include "Core/Engine.h"

class REngineFactory
{
public:
	REngineFactory();

	static REngine *CreateEngine();
};