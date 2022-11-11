#pragma once
#include"../Mesh/MeshType.h"
#include<string>
#include<vector>

class aiMaterial;
class MeshGroup;
class ObjectAnalysisByAssimp
{
public:
	ObjectAnalysisByAssimp();
	~ObjectAnalysisByAssimp();
	void LoadMesh(std::string fileName, std::string name, const XMFLOAT3& newPosition, bool IsRight);

	std::string GetFilePath(bool IsRight, std::string ObjName, std::string TexName);
	std::string GetTexName(std::string ObjName, std::string TexName);

	void SetMaterialTex(aiMaterial* pMaterial, MeshGroup* pMeshGroup, std::string meshName, std::string ObjName, bool  IsRight);
private:
};