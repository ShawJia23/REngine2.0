#pragma once
#include"../ActorObject.h"
#include"../../Component/Light/ParallelLightComponent.h"

class GParallelLight :public GActorObject
{
	RVARIABLE()
		RParallelLightComponent* m_ParallelLightComponent;
public:
};