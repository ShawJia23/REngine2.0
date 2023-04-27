#pragma once
#include "../Manage/MeshManage.h"
#include"Construction/ObjectConstruction.h"

namespace MeshConstruction
{
    template<class T, typename ...Args>
    T* CreateMeshComponent(T* mesh, EMeshRenderLayerType type, Args &&... rest)
    {
        size_t hashKey = 0;
        mesh->BuildKey(hashKey, forward<Args>(rest)...);
        mesh->SetMeshRenderLayerType(type);
        std::shared_ptr<RRenderData> RenderingData;
        if (DXRenderEngine::getInstance().GetDX12Pipeline()->FindMeshRenderingDataByHash(
            hashKey, RenderingData, (int)mesh->GetRenderLayerType()))
        {
            DXRenderEngine::getInstance().GetDX12Pipeline()->DuplicateMesh(mesh, RenderingData);
        }
        else
        {
            MeshRenderData meshData;
            mesh->CreateMesh(meshData, forward<Args>(rest)...);
            DXRenderEngine::getInstance().GetDX12Pipeline()->BuildMesh(hashKey, mesh, meshData);
        }
        mesh->Init();

        return mesh;
    }


    template<class T, typename ...Args>
    T* CreateMeshComponent(const CreateObjectParam& inObjectParam, EMeshRenderLayerType type, Args &&...rest)
    {
        T* mesh = CreateObject<T>(inObjectParam, new T());//NewObject

        return CreateMeshComponent<T>(mesh, type, rest...);

        return NULL;
    }
}