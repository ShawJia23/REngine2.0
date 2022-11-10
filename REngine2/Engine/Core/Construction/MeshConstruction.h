#pragma once
#include "../../Manage/MeshManage.h"
#include"ObjectConstruction.h"

namespace MeshConstruction
{
    template<class T, typename ...ParamTypes>
    T* CreateMeshComponent(RMeshManage* manage, ParamTypes &&...Params)
    {
        if (manage)
        {
            T* mesh = new T();

            //��ȡģ����Դ
            MeshRenderData meshData;
            mesh->CreateMesh(meshData, forward<ParamTypes>(Params)...);

            mesh->Init();

            manage->GetDX12Pipeline().BuildMesh(mesh, meshData);
            return mesh;
        }

        return NULL;
    }
}