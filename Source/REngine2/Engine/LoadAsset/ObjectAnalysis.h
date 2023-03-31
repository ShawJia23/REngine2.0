#pragma once
#include"../Mesh/MeshType.h"
#include<string>
#include<vector>

class aiMaterial;
class MeshGroup;

struct RAssimpMaterial
{
	std::string DiffuseMapFileName;
	std::string SpecularMapFileName;
	std::string AlphaMapFileName;
	std::string BumpMapFileName;
};

//Model
struct RAssimpModel
{
	std::vector<MeshRenderData> MeshData;
	std::map<int, RAssimpMaterial> MaterialMap;
};

struct RAssimpObj
{
	std::vector<RAssimpModel> ModelData;
};

std::vector<std::string> StringSplit(const std::string& str, char delim);

class ObjectAnalysisByAssimp
{
public:
	ObjectAnalysisByAssimp();
	~ObjectAnalysisByAssimp();
	void LoadMesh(std::string fileName, std::string name, 
		const XMFLOAT3& newPosition, const fvector_3d& newScale, 
		bool IsRight,MeshGroup* outMeshData);

	std::string GetFilePath(bool IsRight, std::string ObjName, std::string TexName);
	std::string GetTexName(std::string ObjName, std::string TexName);
	void LoadMeshData(const char* InPath, RAssimpObj& OutData);
	void SetMaterialTex(aiMaterial* pMaterial, MeshGroup* pMeshGroup, std::string meshName, std::string ObjName, bool  IsRight);
private:
};