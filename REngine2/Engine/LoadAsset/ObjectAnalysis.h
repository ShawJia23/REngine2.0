#pragma once
#include"../Mesh/MeshType.h"
#include<string>
#include<vector>

class ObjectAnalysisByAssimp
{
public:
	ObjectAnalysisByAssimp();
	~ObjectAnalysisByAssimp();
	void LoadMesh(std::string fileName, std::string name);
private:
};