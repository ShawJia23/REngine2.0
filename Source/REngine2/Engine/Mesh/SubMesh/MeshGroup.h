#pragma once
#include"../../Interface/DXDeviceInterface.h"
#include"../../Mesh/MeshType.h"

class BMesh;
class RMeshComponent;
class MeshGroup: public IDirectXDeviceInterface
{
public:
	MeshGroup();

	struct SubMesh
	{
		SubMesh();
		BMesh* Mesh;
		MeshRenderData MeshData;
		size_t outKey;
	};

	void AddSubmesh(std::string name, RMeshComponent* mesh, MeshRenderData MeshData);
	void CreateMesh();
	void AddTexture(std::string objName, std::string texName, std::string fileName, int type);
	void CreateTexture();

	void SetPosition(const XMFLOAT3& newPosition);
private:
	std::unordered_map<std::string, SubMesh> m_RenderDatas;
};