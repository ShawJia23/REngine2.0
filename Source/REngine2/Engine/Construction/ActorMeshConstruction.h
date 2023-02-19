#pragma once
#include "MeshConstruction.h"

namespace ActorMeshConstruction
{
	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderData(const CreateObjectParam& inObjectParam, RMeshManage* manage,EMeshRenderLayerType type,ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(inObjectParam,manage, type,Params...);
	}

	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderDataByComponent(RMeshManage* InManage, T* InMeshComponent, ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(InManage, InMeshComponent, InMeshComponent->GetRenderLayerType(), Params...);
	}
}