#pragma once
#include "Engine.h"

class REngineFactory
{
public:
	REngineFactory();

	static REngine *CreateEngine();
};