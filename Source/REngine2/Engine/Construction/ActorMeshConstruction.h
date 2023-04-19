#pragma once
#include "MeshConstruction.h"

namespace ActorMeshConstruction
{
	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderData(const CreateObjectParam& inObjectParam,EMeshRenderLayerType type,ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(inObjectParam, type,Params...);
	}

	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderDataByComponent(T* InMeshComponent, ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(InMeshComponent, InMeshComponent->GetRenderLayerType(), Params...);
	}
}