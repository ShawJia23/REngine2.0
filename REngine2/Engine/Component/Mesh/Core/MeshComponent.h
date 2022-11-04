#pragma once
#include"../../TransformComponent/TransformComponent.h"
#include"../../../Materials/Material.h"

struct MeshRenderData;
class RMeshComponent :public RTransformComponent
{
	RVARIABLE()
	vector<RMaterial*>	m_Materials;
public:
	RMeshComponent();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderData* InRenderingData);

	UINT GetMaterialsNum() { return m_Materials.size(); }

	vector<RMaterial*>* GetMaterials() { return &m_Materials; }
};
