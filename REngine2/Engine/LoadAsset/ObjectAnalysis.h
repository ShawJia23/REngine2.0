#pragma once
#include"../Mesh/Core/MeshType.h"
#include<string>
#include<vector>

class ObjectAnalysisByAssimp
{
public:
	ObjectAnalysisByAssimp();
	~ObjectAnalysisByAssimp();
	void LoadMesh(MeshRenderData& meshData, std::string fileName);
private:
};