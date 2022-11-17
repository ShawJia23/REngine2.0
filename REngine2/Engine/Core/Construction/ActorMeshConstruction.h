#pragma once
#include "MeshConstruction.h"
#include "../../Mesh/Mesh.h"

namespace ActorMeshConstruction
{
	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderData(RMeshManage* manage, EMeshRenderLayerType type,ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(manage, type,Params...);
	}
}