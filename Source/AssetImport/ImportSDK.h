#pragma once

#include <vector>
#include <string>
#include <map>

#ifdef RASSETSDK_EXPORTS
#define RASSETIMPORT_API __declspec(dllexport)
#else
#define RASSETIMPORT_API __declspec(dllimport)
#endif // EEE

//2D向量
struct RImportVector2
{
	RImportVector2()
		:X(0.f)
		,Y(0.f)
	{}
	float X;
	float Y;
};

//3D向量
struct RImportVector3:public RImportVector2
{
	RImportVector3()
		:RImportVector2()
		,Z(0.f)
	{}

	float Z;
};

//顶点数据
struct RASSETIMPORT_API RImportVertex
{
	RImportVector3 Position;
	RImportVector3 Color;
	RImportVector3 Normal;
	RImportVector3 Tangent;
	RImportVector2 UV;
	RImportVector3 Binormal;
};

//我们提取的数据一定是三角形
struct RASSETIMPORT_API RImportTriangle
{
	RImportTriangle()
	:MaterialID(0)
	{}

	RImportVertex Vertexs[3];
	int MaterialID;
};

//模型数据
struct RASSETIMPORT_API RImportMesh
{
	RImportMesh()
		:MaterialID(0)
	{}
	std::vector<RImportTriangle> VertexData;
	std::vector<uint16_t> IndexData;
	int MaterialID;
};

//材质名称
struct RASSETIMPORT_API RImportMaterial
{
	std::string DiffuseMapFileName;
	std::string SpecularMapFileName;
	std::string AmbientMapFileName;
	std::string NormalsMapFileName;
};

//Model
struct RASSETIMPORT_API RImportModel
{
	std::vector<RImportMesh> MeshData;
	std::map<int, RImportMaterial> MaterialMap;
};

//渲染数据
struct RASSETIMPORT_API RImportRenderData
{
	std::vector<RImportModel> ModelData;
};

struct RASSETIMPORT_API RImportVersion
{
	int Major;
	int Minor;
	int Revision;
};

struct RAssimpVector2
{
	RAssimpVector2()
		:X(0.f)
		, Y(0.f)
	{}
	float X;
	float Y;
};

//3D向量
struct RAssimpVector3 :public RAssimpVector2
{
	RAssimpVector3()
		:RAssimpVector2()
		, Z(0.f)
	{}
	float Z;
};

struct RAssimpVector4 :public RAssimpVector3
{
	RAssimpVector4()
		:RAssimpVector3()
		, W(0.f)
	{}

	float W;
};

struct RASSETIMPORT_API RAssimpMaterial
{
	std::string DiffuseMapFileName;
	std::string SpecularMapFileName;
	std::string AmbientMapFileName;
	std::string NormalsMapFileName;
};

struct RASSETIMPORT_API RAssimpVertex
{
	RAssimpVector3 Position;
	RAssimpVector4 Color;
	RAssimpVector3 Normal;
	RAssimpVector3 TangentU;
	RAssimpVector2 TexC;
};


struct RASSETIMPORT_API RAssimpData
{
	std::vector<RAssimpVertex> VertexData;
	std::vector<uint16_t> IndexData;
};

//Model
struct RASSETIMPORT_API RAssimpModel
{
	std::vector<RAssimpData> MeshData;
	std::map<int, RAssimpMaterial> MaterialMap;
};

struct RASSETIMPORT_API RAssimpObj
{
	std::vector<RAssimpModel> ModelData;
};

struct RAssetImport
{
	RASSETIMPORT_API static void LoadMeshData(const char *InPath,RImportRenderData &OutData);
	RASSETIMPORT_API static void LoadMeshData(const char* InPath, const char* InName, RAssimpObj& OutData);
}; 

