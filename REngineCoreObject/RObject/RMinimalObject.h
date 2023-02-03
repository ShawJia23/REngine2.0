#pragma once
#include"GuidInterface.h"
#include"../Reflection/CodeReflection.h"
#include"../Construction/ObjectConstruction.h"

class RENGINECOREOBJECT_API RMinimalObject :public IGuidInterface
{
public:
	RMinimalObject();
	virtual ~RMinimalObject();

	virtual void Init() {};
	virtual void Tick(float DeltaTime) {};

	bool IsTick() { return bTick; }
	void SetTick(bool tick) { bTick=tick; }

	FORCEINLINE RMinimalObject* GetOuter() const { return Outer; }
	FORCEINLINE std::string GetName() const { return m_Name; }
	void SetOuter(RMinimalObject* InNewOuter) { Outer = InNewOuter; }
	void Rename(const std::string& name) { m_Name = name; }
	protected:
		bool bTick;
		RMinimalObject* Outer;
		std::string m_Name;
};


extern vector<RMinimalObject*> GRObjects;