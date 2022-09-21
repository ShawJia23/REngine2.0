#pragma once
#include "MeshType.h"
#include"../../Core/RObject/RMinimalObject.h"
#include "../../Render/Render.h"
#include "../../Shader/Shader.h"

class BMesh : public RMinimalObject, public IRenderingInterface
{
public:
	BMesh();

	virtual void Init();

	virtual void BuildMesh(const MeshRenderingData* InRenderingData);

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);
};