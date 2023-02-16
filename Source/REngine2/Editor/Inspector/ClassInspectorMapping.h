#pragma once
#include"InspectorMapping.h"
#include"RObject/RMinimalObject.h"
#include"Component/RComponent.h"
class ClassInspectorMapping :public RInspectorMapping
{
public:
	virtual void UpdateDetailsWidget(RMinimalObject* InCoreMinimalObject);

public:
	static shared_ptr<ClassInspectorMapping> MakeDetailsMapping() { return nullptr; }
};


class ActorObjectInspectorMapping :public ClassInspectorMapping
{
public:
	virtual void UpdateDetailsWidget(RMinimalObject* InCoreMinimalObject);

	void ShowPlaceholderObject(RComponent* InComponent, int ID);
public:
	static shared_ptr<ClassInspectorMapping> MakeDetailsMapping();
};