#pragma once
#include"../TransformComponent/TransformComponent.h"
#include"../../Materials/Material.h"
#include"../../Render/Pipeline/RenderLayer/RenderLayerType.h"
#include"MeshComponent.CodeReflection.h"
struct MeshRenderData;
class RMeshComponent :public RTransformComponent
{
	CODEREFLECTION()

	RVARIABLE()
	vector<RMaterial*>	m_Materials;
public:
	RMeshComponent();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderData* InRenderingData);

	UINT GetMaterialsNum() { return m_Materials.size(); }

	vector<RMaterial*>* GetMaterials() { return &m_Materials; }

	void SetMeshRenderLayerType(EMeshRenderLayerType renderLayerType) { MeshRenderLayerType =renderLayerType; }

	EMeshRenderLayerType GetRenderLayerType()const { return MeshRenderLayerType; }

protected:
	EMeshRenderLayerType MeshRenderLayerType;
};
