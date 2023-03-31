#pragma once

#include <vector>
#include <string>
#include <map>

#ifdef RASSETSDK_EXPORTS
#define RASSETIMPORT_API __declspec(dllexport)
#else
#define RASSETIMPORT_API __declspec(dllimport)
#endif // EEE

//2D����
struct RImportVector2
{
	RImportVector2()
		:X(0.f)
		,Y(0.f)
	{}
	float X;
	float Y;
};

//3D����
struct RImportVector3:public RImportVector2
{
	RImportVector3()
		:RImportVector2()
		,Z(0.f)
	{}

	float Z;
};

//��������
struct RASSETIMPORT_API RImportVertex
{
	RImportVector3 Position;
	RImportVector3 Color;
	RImportVector3 Normal;
	RImportVector3 Tangent;
	RImportVector2 UV;
	RImportVector3 Binormal;
};

//������ȡ������һ����������
struct RASSETIMPORT_API RImportTriangle
{
	RImportTriangle()
	:MaterialID(0)
	{}

	RImportVertex Vertexs[3];
	int MaterialID;
};

//ģ������
struct RASSETIMPORT_API RImportMesh
{
	RImportMesh()
		:MaterialID(0)
	{}
	std::vector<RImportTriangle> VertexData;
	std::vector<uint16_t> IndexData;
	int MaterialID;
};

//��������
struct RASSETIMPORT_API RImportMaterial
{
	std::string DiffuseMapFileName;
	std::string SpecularMapFileName;
	std::string AlphaMapFileName;
	std::string BumpMapFileName;
};

//Model
struct RASSETIMPORT_API RImportModel
{
	std::vector<RImportMesh> MeshData;
	std::map<int, RImportMaterial> MaterialMap;
};

//��Ⱦ����
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

struct RAssetImport
{
	RASSETIMPORT_API void LoadMeshData(const char *InPath,RImportRenderData &OutData);
}; 
