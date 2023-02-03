#pragma once
#include"../RCoreObjectMinimal.h"
#include"../RObjectMacro.h"
class RMinimalObject;

struct RENGINECOREOBJECT_API CreateObjectParam
{
	CreateObjectParam()
		:Outer(NULL), Name("NULL")
	{}

	RMinimalObject* Outer;
	std::string Name;
};

template<class T>
T* CreateObject(const CreateObjectParam& inObjectParam, RMinimalObject* newObject)
{
	T* obj = dynamic_cast<T*>(newObject);
	obj->SetOuter(inObjectParam.Outer);
	obj->Rename(inObjectParam.Name);
	return obj;
}

template<class T, typename ...ParamTypes>
T* ConstructionObject(ParamTypes &&...Params)
{
	return CreateObject<T>(new T(Params...));
}