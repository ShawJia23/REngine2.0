#pragma once

#include"ViewPort/Viewport.h"
#include"RObject/RMinimalObject.h"

struct RInputKey;
class RTransformComponent;
class RInputComponent;
class RCamera;
class GActorObject;
class RWorld :public RMinimalObject 
{
public:
	RWorld();

	RCamera* GetCamera() { return m_camera; }

	template<class T>
	T* CreateActorObject()
	{
		T* InArray = new T();
		InArray->SetOuter(this);
		InArray->InitMinimalObject();
		ActorObjects.push_back(InArray);

		return InArray;
	}
	const vector<GActorObject*>& GetActors() const { return ActorObjects; }
protected:
	RVARIABLE()
	RCamera* m_camera;

	//´æ´¢ÎÒÃÇµÄActors
	RVARIABLE()
	vector<GActorObject*> ActorObjects;
};