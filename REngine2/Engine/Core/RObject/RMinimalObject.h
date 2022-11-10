#pragma once
#include"GuidInterface.h"
#include"../../EngineMinimal.h"
#include"../../Platform/Windows/WindowsPlatform.h"
#include"../../Reflection/CodeReflectionMacro.h"

class RMinimalObject :public IGuidInterface
{
public:
	RMinimalObject();
	virtual ~RMinimalObject();

	virtual void Init() {};
	virtual void Tick(float DeltaTime) {};

	bool IsTick() { return bTick; }
	void SetTick(bool tick) { bTick=tick; }
	protected:
		bool bTick;
};


extern vector<RMinimalObject*> GRObjects;