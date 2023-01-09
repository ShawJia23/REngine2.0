#pragma once
#include "MeshConstruction.h"
#include "../../Mesh/Mesh.h"

namespace ActorMeshConstruction
{
	template<class T, typename ...ParamTypes>
	T* CreateMeshRenderData(const CreateObjectParam& inObjectParam, RMeshManage* manage,EMeshRenderLayerType type,ParamTypes &&...Params)
	{
		return MeshConstruction::CreateMeshComponent<T>(inObjectParam,manage, type,Params...);
	}
}