#pragma once
#include"../RCoreObjectMinimal.h"
#include"../RObjectMacro.h"
#include"ConstructionComponents.h"
class RMinimalObject;
class RComponent;
struct RENGINECOREOBJECT_API CreateObjectParam
{
	CreateObjectParam()
		:Outer(NULL),
		ParentComponent(NULL)
	{}

	RMinimalObject* Outer;
	RComponent* ParentComponent;
};

template<class T>
T* CreateObject(const CreateObjectParam& inObjectParam, RMinimalObject* newObject)
{
	ConstructionComponent::ConstructionComponents(inObjectParam, newObject);

	T* obj = dynamic_cast<T*>(newObject);
	obj->SetOuter(inObjectParam.Outer);
	obj->InitMinimalObject();
	return obj;
}

template<class T, typename ...ParamTypes>
T* ConstructionObject(const CreateObjectParam& InObjectParam, ParamTypes &&...Params)
{
	return CreateObject<T>(InObjectParam, new T(Params...));
}