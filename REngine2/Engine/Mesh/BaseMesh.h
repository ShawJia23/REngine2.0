#pragma once
#include "Mesh.h"
class BoxMesh :public BMesh
{
	typedef BMesh Super;
public:
	BoxMesh();
	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float height,float width,float depth);
};

class ConeMesh :public BMesh
{
	typedef BMesh Super;
public:
	ConeMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float radius, float height, uint32_t axialSub, uint32_t heightSub);
};

class CylinderMesh :public BMesh
{
	typedef BMesh Super;
public:
	CylinderMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float topRadius, float bottomRadius, float height, uint32_t axialSub, uint32_t heightSub);
};

class PlaneMesh :public BMesh
{
	typedef BMesh Super;
public:
	PlaneMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float height, float width, uint32_t heightSub, uint32_t widthSub);
};

class SphereMesh :public BMesh
{
	typedef BMesh Super;
public:
	SphereMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh(float radius, uint32_t axialSub, uint32_t heightSub);
};

class CustomMesh :public BMesh
{
	typedef BMesh Super;
public:
	CustomMesh();

	virtual void Init();

	virtual void Draw(float DeltaTime);

	void CreateMesh();
};


class MeshGroup: public IDirectXDeviceInterface
{
public:
	MeshGroup();

	struct SubMesh
	{
		SubMesh();
		CustomMesh* Mesh;
		MeshRenderData MeshData;
	};

	void AddSubmesh(std::string name,RMeshComponent* mesh, MeshRenderData MeshData);
	void CreateMesh();
	void AddTexture(std::string objName, std::string texName, std::string fileName, int type);
	void CreateTexture();

	void SetPosition(const XMFLOAT3& newPosition);
private:
	std::unordered_map<std::string, SubMesh> m_RenderDatas;
};