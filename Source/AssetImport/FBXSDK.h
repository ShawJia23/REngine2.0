#pragma once

#include <vector>
#include <string>
#include <map>

#ifdef FBXSDK_EXPORTS
#define FBXASSETIMPORT_API __declspec(dllexport)
#else
#define FBXASSETIMPORT_API __declspec(dllimport)
#endif // EEE

//2D����
struct RFBXVector2
{
	RFBXVector2()
		:X(0.f)
		,Y(0.f)
	{}
	float X;
	float Y;
};

//3D����
struct RFBXVector3:public RFBXVector2
{
	RFBXVector3()
		:RFBXVector2()
		,Z(0.f)
	{}

	float Z;
};

//��������
struct FBXASSETIMPORT_API RFBXVertex
{
	RFBXVector3 Position;
	RFBXVector3 Color;
	RFBXVector3 Normal;
	RFBXVector3 Tangent;
	RFBXVector2 UV;
	RFBXVector3 Binormal;
};

//������ȡ������һ����������
struct FBXASSETIMPORT_API RFBXTriangle
{
	RFBXTriangle()
	:MaterialID(0)
	{}

	RFBXVertex Vertexs[3];
	int MaterialID;
};

//ģ������
struct FBXASSETIMPORT_API RFBXMesh
{
	RFBXMesh()
		:MaterialID(0)
	{}
	std::vector<RFBXTriangle> VertexData;
	std::vector<uint16_t> IndexData;
	int MaterialID;
};

//��������
struct FBXASSETIMPORT_API RFBXMaterial
{
	std::string DiffuseMapFileName;
	std::string SpecularMapFileName;
	std::string AlphaMapFileName;
	std::string BumpMapFileName;
};

//Model
struct FBXASSETIMPORT_API RFBXModel
{
	std::vector<RFBXMesh> MeshData;
	std::map<int, RFBXMaterial> MaterialMap;
};

//��Ⱦ����
struct FBXASSETIMPORT_API RFBXRenderData
{
	std::vector<RFBXModel> ModelData;
};

struct FBXASSETIMPORT_API RFBXVersion
{
	int Major;
	int Minor;
	int Revision;
};

struct RFBXAssetImport
{
	FBXASSETIMPORT_API void LoadMeshData(const char *InPath,RFBXRenderData &OutData);
}; 
