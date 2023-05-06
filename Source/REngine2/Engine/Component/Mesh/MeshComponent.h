#pragma once
#include"../TransformComponent/TransformComponent.h"
#include"../../Materials/Material.h"
#include"../../Render/Pipeline/RenderLayer/RenderLayerType.h"
#include"MeshComponent.CodeReflection.h"
struct MeshRenderData;
class RMeshComponent :public RTransformComponent
{
	CODEREFLECTION()

public:
	RVARIABLE(CodeType = Resources, Category = Mesh)
	vector<RMaterial*> m_Materials;

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

	void SetShadow(bool bNewShadow) { bCastShadow = bNewShadow; }
	bool IsShadow()const { return bCastShadow; }

protected:
	RVARIABLE(CodeType = Resources, Category = Mesh, Draggable)
	bool bVisible;
	RVARIABLE(CodeType = Resources, Category = Mesh, Draggable)
	bool bPickup;
	RVARIABLE(CodeType = Resources, Category = Mesh, Draggable)
	bool bCastShadow;
	EMeshRenderLayerType MeshRenderLayerType;
};
