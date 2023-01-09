#pragma once
#include "../../Manage/MeshManage.h"
#include"ObjectConstruction.h"

namespace MeshConstruction
{
    template<class T, typename ...Args>
    T* CreateMeshComponent(RMeshManage* manage, T* mesh,EMeshRenderLayerType type, Args &&... rest)
    {
        if (manage)
        {
            size_t hashKey = 0;
            mesh->BuildKey(hashKey, forward<Args>(rest)...);
            mesh->SetMeshRenderLayerType(type);
            std::shared_ptr<RRenderData> RenderingData;
            if (manage->GetDX12Pipeline().FindMeshRenderingDataByHash(
                hashKey, RenderingData, (int)mesh->GetRenderLayerType())) 
            {
                manage->GetDX12Pipeline().DuplicateMesh(mesh, RenderingData);
            }
            else 
            {
                MeshRenderData meshData;
                mesh->CreateMesh(meshData, forward<Args>(rest)...);
                manage->GetDX12Pipeline().BuildMesh(hashKey, mesh, meshData);
            }
            mesh->Init();

            return mesh;
        }

        return NULL;
    }


    template<class T, typename ...Args>
    T* CreateMeshComponent(const CreateObjectParam& inObjectParam, RMeshManage* manage, EMeshRenderLayerType type, Args &&...rest)
    {
        if (manage)
        {
            T* mesh = CreateObject<T>(inObjectParam, new T());//NewObject

            return CreateMeshComponent<T>(manage, mesh, type,rest...);
        }

        return NULL;
    }
}