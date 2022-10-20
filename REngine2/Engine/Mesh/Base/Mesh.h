#pragma once
#include "MeshType.h"
#include"../../Core/RObject/RMinimalObject.h"
#include "../../Render/Render.h"
#include "../../Shader/Shader.h"
#include"../../Actor/ActorObject.h"
#include"../Materials/Material.h"

class BMesh : public GActorObject, public IRenderingInterface
{
	RVARIABLE()
	vector<RMaterial*>	m_Materials;
public:
	BMesh();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderData* InRenderingData);

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

	UINT GetMaterialsNum() { return m_Materials.size(); }
};