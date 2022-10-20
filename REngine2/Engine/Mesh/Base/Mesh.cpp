#include "Mesh.h"
#include"../../Config/RenderConfig.h"
#include"../../Render/ResourcesUpdate.h"

BMesh::BMesh():GActorObject()
{
	m_Materials.push_back(CreateObject<RMaterial>(new RMaterial()));
}

void BMesh::Init()
{
}

void BMesh::BuildMesh(const MeshRenderData* InRenderingData)
{
}

void BMesh::PreDraw(float DeltaTime)
{
}

void BMesh::Draw(float DeltaTime)
{
}

void BMesh::PostDraw(float DeltaTime)
{
}

