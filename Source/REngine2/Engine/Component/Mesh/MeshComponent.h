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
public:
	void SetPickup(bool bNewPickup) { bPickup = bNewPickup; }
	bool IsPickup()const { return bPickup; }

	void SetVisible(bool bNewVisible) { bVisible = bNewVisible; }
	bool IsVisible()const { return bVisible; }

protected:
	bool bVisible;
	bool bPickup;

	EMeshRenderLayerType MeshRenderLayerType;
};
