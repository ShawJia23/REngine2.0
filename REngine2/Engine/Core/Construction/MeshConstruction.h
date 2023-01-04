#pragma once
#include "../../Manage/MeshManage.h"
#include"ObjectConstruction.h"

namespace MeshConstruction
{
    template<class T, typename ...Args>
    T* CreateMeshComponent(RMeshManage* manage, EMeshRenderLayerType type, Args &&... rest)
    {
        if (manage)
        {
            T* mesh = new T();

            size_t hashKey = 0;
            mesh->BuildKey(hashKey, forward<Args>(rest)...);

            std::shared_ptr<RRenderData> RenderingData;
            manage->GetDX12Pipeline().FindMeshRenderingDataByHash(
                hashKey, RenderingData, (int)mesh->GetRenderLayerType());

            MeshRenderData meshData;
            mesh->CreateMesh(meshData, forward<Args>(rest)...);

            mesh->Init();

            mesh->SetMeshRenderLayerType(type);

            manage->GetDX12Pipeline().BuildMesh(hashKey,mesh, meshData);

            return mesh;
        }

        return NULL;
    }
}