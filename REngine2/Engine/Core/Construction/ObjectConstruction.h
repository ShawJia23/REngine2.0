#pragma once

class RMinimalObject;

template<class T>
T* CreateObject(RMinimalObject* NewObject)
{
	return dynamic_cast<T*>(NewObject);
}

template<class T, typename ...ParamTypes>
T* ConstructionObject(ParamTypes &&...Params)
{
	return CreateObject<T>(new T(Params...));
}