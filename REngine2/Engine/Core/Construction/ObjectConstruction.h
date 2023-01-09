#pragma once

class RMinimalObject;

struct CreateObjectParam
{
	CreateObjectParam()
		:Outer(NULL)
	{}

	RMinimalObject* Outer;
};

template<class T>
T* CreateObject(const CreateObjectParam& inObjectParam,RMinimalObject* newObject)
{
	T* obj = dynamic_cast<T*>(newObject);
	obj->SetOuter(inObjectParam.Outer);
	return obj;
}

template<class T, typename ...ParamTypes>
T* ConstructionObject(ParamTypes &&...Params)
{
	return CreateObject<T>(new T(Params...));
}