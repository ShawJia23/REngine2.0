#include "ThirdPartyLibrary/FBX/include/fbxsdk.h"
#include "ImportSDK.h"
#include"ImportExport.h"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#pragma comment(lib, "libfbxsdk.lib")
#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libfbxsdk-mt.lib")

void InitializeSdkObjects(FbxManager*& InManager, FbxScene*& InScene)
{
	InManager = FbxManager::Create();

	FbxIOSettings *FBXIO = FbxIOSettings::Create(InManager, IOSROOT);
	InManager->SetIOSettings(FBXIO);

	FbxString FBXPath = FbxGetApplicationDirectory();
	InManager->LoadPluginsDirectory(FBXPath);

	InScene = FbxScene::Create(InManager,"OK My");
}

bool LoadScene(FbxManager* InManager, FbxDocument* InScene, const char* InFilename)
{
	RImportVersion SDKVersion;
	FbxManager::GetFileFormatVersion(
		SDKVersion.Major,
		SDKVersion.Minor,
		SDKVersion.Revision);

	FbxImporter* FBXImporterPtr = FbxImporter::Create(InManager,"");

	bool bReturn = FBXImporterPtr->Initialize(
		InFilename,
		-1,
		InManager->GetIOSettings());

	RImportVersion FileVersion;
	FBXImporterPtr->GetFileVersion(
		FileVersion.Major,
		FileVersion.Minor,
		FileVersion.Revision);

	if (!bReturn)
	{
		return false;
	}

	if (FBXImporterPtr->IsFBX())
	{
		//��ӡ����
	}

	bReturn = FBXImporterPtr->Import(InScene);
	if (bReturn && 
		FBXImporterPtr->GetStatus().GetCode() == FbxStatus::ePasswordError)
	{
		//����
	}

	//ɾ��
	FBXImporterPtr->Destroy();

	return true;
}

void GetPolygons(FbxMesh* InMesh, RImportMesh& OutData)
{
	int PolygonCount = InMesh->GetPolygonCount();
	FbxVector4* ControlPoints = InMesh->GetControlPoints();

	int VertexID = 0;
	for (int i = 0; i < PolygonCount; i++)//ͼԪ
	{
		OutData.VertexData.push_back(RImportTriangle());
		RImportTriangle &InTriangle = OutData.VertexData[OutData.VertexData.size() - 1];
		
		int PolygonSize = InMesh->GetPolygonSize(i);
		for (int j = 0; j < PolygonSize; j++)
		{
			int ControlPointIndex = InMesh->GetPolygonVertex(i, j);

			//Coordinates
			//�õ�λ��
			//FbxVector4 Coordinates;
			//��ȡλ��
			{
				//��������
				FbxDouble3 Scaling = InMesh->GetNode()->LclScaling;

				InTriangle.Vertexs[j].Position.X = ControlPoints[ControlPointIndex].mData[0] * Scaling[0];
				InTriangle.Vertexs[j].Position.Y = ControlPoints[ControlPointIndex].mData[2] * Scaling[2];
				InTriangle.Vertexs[j].Position.Z = -ControlPoints[ControlPointIndex].mData[1] * Scaling[1];
			}

			//������ɫ
			for (int l = 0; l < InMesh->GetElementVertexColorCount(); l++){}

			//UV
			for (int l = 0; l < InMesh->GetElementUVCount(); ++l)
			{
				FbxGeometryElementUV* TextureUV = InMesh->GetElementUV(l);
				auto ModeType = TextureUV->GetMappingMode();

				auto ReferenceMode = TextureUV->GetReferenceMode();
				if (ModeType == fbxsdk::FbxLayerElement::eByControlPoint)
				{
					if (ReferenceMode == fbxsdk::FbxLayerElement::eDirect)
					{
						FbxVector2 UV = TextureUV->GetDirectArray().GetAt(ControlPointIndex);

						InTriangle.Vertexs[j].UV.X = UV.mData[0];
						InTriangle.Vertexs[j].UV.Y = 1.f - UV.mData[1];//V�Ƿ��� DX �� OpenGL��һ��
					}
					else if (ReferenceMode == fbxsdk::FbxLayerElement::eIndexToDirect)
					{
						int ID = TextureUV->GetIndexArray().GetAt(ControlPointIndex);

						FbxVector2 UV = TextureUV->GetDirectArray().GetAt(ID);
						InTriangle.Vertexs[j].UV.X = UV.mData[0];
						InTriangle.Vertexs[j].UV.Y = 1.f - UV.mData[1];//V�Ƿ��� DX �� OpenGL��һ��
					}
				}
				else if (ModeType == fbxsdk::FbxLayerElement::eByPolygonVertex)
				{
					int TextureUVIndex = InMesh->GetTextureUVIndex(i, j);
					FbxVector2 UV = TextureUV->GetDirectArray().GetAt(TextureUVIndex);
					switch (ReferenceMode)
					{
						case fbxsdk::FbxLayerElement::eDirect:
						case fbxsdk::FbxLayerElement::eIndexToDirect:
						{
							FbxVector2 UV = TextureUV->GetDirectArray().GetAt(ControlPointIndex);

							InTriangle.Vertexs[j].UV.X = UV.mData[0];
							InTriangle.Vertexs[j].UV.Y = 1.f - UV.mData[1];//V�Ƿ��� DX �� OpenGL��һ��
							break;
						}
					}
				}
			}

			//����
			for (int l = 0; l < InMesh->GetElementNormalCount(); ++l)
			{
				FbxGeometryElementNormal* Normal = InMesh->GetElementNormal(l);
				auto NormalReferenceMode = Normal->GetReferenceMode();

				if (Normal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (NormalReferenceMode)
					{
						case fbxsdk::FbxLayerElement::eDirect:
						{
							FbxVector4 NormalPoint = Normal->GetDirectArray().GetAt(VertexID);
							
							InTriangle.Vertexs[j].Normal.X = NormalPoint.mData[0];
							InTriangle.Vertexs[j].Normal.Y = NormalPoint.mData[2];
							InTriangle.Vertexs[j].Normal.Z = NormalPoint.mData[1];
							
							break;
						}
						case fbxsdk::FbxLayerElement::eIndexToDirect:
						{
							int ID = Normal->GetIndexArray().GetAt(VertexID);

							FbxVector4 NormalPoint = Normal->GetDirectArray().GetAt(ID);
							InTriangle.Vertexs[j].Normal.X = NormalPoint.mData[0];
							InTriangle.Vertexs[j].Normal.Y = NormalPoint.mData[2];
							InTriangle.Vertexs[j].Normal.Z = NormalPoint.mData[1];
						}
					}
				}
				else if (Normal->GetMappingMode() == FbxGeometryElement::eByControlPoint)
				{
					switch (NormalReferenceMode)
					{
						case fbxsdk::FbxLayerElement::eDirect:
						{
							FbxVector4 NormalPoint = Normal->GetDirectArray().GetAt(ControlPointIndex);
							InTriangle.Vertexs[j].Normal.X = NormalPoint.mData[0];
							InTriangle.Vertexs[j].Normal.Y = NormalPoint.mData[2];
							InTriangle.Vertexs[j].Normal.Z = NormalPoint.mData[1];
							break;
						}
						case fbxsdk::FbxLayerElement::eIndexToDirect:
						{
							int ID = Normal->GetIndexArray().GetAt(ControlPointIndex);
							FbxVector4 NormalPoint = Normal->GetDirectArray().GetAt(ID);
							InTriangle.Vertexs[j].Normal.X = NormalPoint.mData[0];
							InTriangle.Vertexs[j].Normal.Y = NormalPoint.mData[2];
							InTriangle.Vertexs[j].Normal.Z = NormalPoint.mData[1];
							break;
						}
					}
				}
			}

			//���� T
			for (int l = 0; l < InMesh->GetElementTangentCount(); ++l)
			{
				FbxGeometryElementTangent* Tangent = InMesh->GetElementTangent(l);

				if (Tangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (Tangent->GetReferenceMode())
					{
						case FbxGeometryElement::eDirect:
						{
							FbxVector4 TangentValue = Tangent->GetDirectArray().GetAt(VertexID);
							
							InTriangle.Vertexs[j].Tangent.X = TangentValue.mData[0];
							InTriangle.Vertexs[j].Tangent.Y = TangentValue.mData[2];
							InTriangle.Vertexs[j].Tangent.Z = TangentValue.mData[1];
							break;
						}
						case FbxGeometryElement::eIndexToDirect:
						{
							int ID = Tangent->GetIndexArray().GetAt(VertexID);
							
							FbxVector4 TangentValue = Tangent->GetDirectArray().GetAt(ID);
							InTriangle.Vertexs[j].Tangent.X = TangentValue.mData[0];
							InTriangle.Vertexs[j].Tangent.Y = TangentValue.mData[2];
							InTriangle.Vertexs[j].Tangent.Z = TangentValue.mData[1];
							break;
						}
					}
				}
			}

			//B
			for (int l = 0; l < InMesh->GetElementBinormalCount(); ++l)
			{
				FbxGeometryElementBinormal* Binormal = InMesh->GetElementBinormal(l);

				if (Binormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
				{
					switch (Binormal->GetReferenceMode())
					{
						case FbxGeometryElement::eDirect:
						{
							Binormal->GetDirectArray().GetAt(VertexID);
							break;
						}
					}
				}
			}

			VertexID++;
		}
	}
}

void GetMaterial(){}

void GetIndex(RImportMesh& InMesh)
{
	uint16_t VertexDataSize = InMesh.VertexData.size() * 3.f;
	InMesh.IndexData.resize(InMesh.VertexData.size() * 3.f);

	for (uint16_t i = 0; i < VertexDataSize; i++)
	{
		InMesh.IndexData[i] = i;
	}
}

void GetMesh(FbxNode* InNode, RImportModel& InModel)
{
	FbxMesh *NodeMesh = (FbxMesh*)InNode->GetNodeAttribute();

	InModel.MeshData.push_back(RImportMesh());
	RImportMesh& InMesh = InModel.MeshData[InModel.MeshData.size() - 1];

	GetPolygons(NodeMesh, InMesh);

	GetIndex(InMesh);

	//GetMaterial();
}

void RecursiveLoadMesh(FbxNode* InNode,RImportRenderData& OutData)
{
	//XML
	if (InNode->GetNodeAttribute() == NULL)
	{
		//NULL Node
	}
	else
	{
		FbxNodeAttribute::EType AttributeType = (InNode->GetNodeAttribute()->GetAttributeType());

		if (AttributeType == fbxsdk::FbxNodeAttribute::eMesh)
		{
			OutData.ModelData.push_back(RImportModel());
			RImportModel &InModel = OutData.ModelData[OutData.ModelData.size() - 1];
			GetMesh(InNode, InModel);
		}
		else if (AttributeType == fbxsdk::FbxNodeAttribute::eSkeleton)
		{

		}
	}

	for (int i = 0; i < InNode->GetChildCount(); i++)
	{
		RecursiveLoadMesh(InNode->GetChild(i), OutData);
	}
}

void DestroySdkObjects(FbxManager* InManager)
{
	if (InManager)
	{
		InManager->Destroy();
	}
}

void RAssetImport::LoadMeshData(const char* InPath, RImportRenderData& OutData)
{
	//������������ͳ���
	FbxManager* SdkManager = NULL;
	FbxScene* Scene = NULL;

	//��ʼ����������
	InitializeSdkObjects(SdkManager,Scene);

	//��ȡFBXģ��
	FbxString FBXPath(InPath);
	bool bResult = LoadScene(SdkManager, Scene, FBXPath.Buffer());

	//FbxAxisSystem::DirectX.ConvertScene(Scene);

	//XML �������ǵ�FBX
	if (FbxNode *Node = Scene->GetRootNode())
	{
		for (int i = 0;i < Node->GetChildCount();i++)
		{
			RecursiveLoadMesh(Node->GetChild(i), OutData);
		}
	}

	//�ɵ�
	DestroySdkObjects(SdkManager);
}

std::vector<std::string> StringSplit(const std::string& str, char delim) {
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}

bool GetLastString(std::string & final, const std::string& str, char delim) {
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	if (elems.size() > 1)
	{
		final += elems.back();
		return true;
	}
	return  false;
}

std::string GetFilePath(std::string ObjName, std::string TexName)
{
	std::string pTexNamePath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineAssetPath()) + "/Model/";;
	pTexNamePath += ObjName;
	pTexNamePath += "/";
	pTexNamePath += "tex";
	pTexNamePath += "/";

	if (GetLastString(pTexNamePath, TexName, '\\'))
		return pTexNamePath;
	if (GetLastString(pTexNamePath, TexName, '/'))
		return pTexNamePath;

	return "";
}

std::string GetTexName(std::string ObjName, std::string TexName)
{
	std::string pTexName = ObjName;
	pTexName += ".";

	GetLastString(pTexName, TexName, '\\');
	GetLastString(pTexName, TexName, '/');

	return pTexName;
}

void RAssimpObject::LoadMeshData(const char* InPath, const char* InName, RAssimpObj& OutData)
{
	Assimp::Importer aiImporter;
	const aiScene* pModel = aiImporter.ReadFile(InPath, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_ConvertToLeftHanded);
	if (nullptr == pModel)
	{
		return;
	}
	if (pModel->HasMeshes())
	{
		for (int num = 0; num < pModel->mNumMeshes; num++)
		{
			OutData.ModelData.push_back(RAssimpModel());
			auto& pImportModel = OutData.ModelData.back();
			aiMesh* pMesh = pModel->mMeshes[num];
			if (pMesh->HasFaces())
			{
				pImportModel.MeshData.push_back(RAssimpData());
				auto& pImportMesh = pImportModel.MeshData.back();
				for (int i = 0; i < pMesh->mNumVertices; i++)
				{
					RAssimpVertex pVertex;
					if (pMesh->mVertices)
					{
						pVertex.Position.X = pMesh->mVertices[i].x;
						pVertex.Position.Y = pMesh->mVertices[i].y;
						pVertex.Position.Z = pMesh->mVertices[i].z;
					}
					if (pMesh->mNormals)
					{
						pVertex.Normal.X = pMesh->mNormals[i].x;
						pVertex.Normal.Y = pMesh->mNormals[i].y;
						pVertex.Normal.Z = pMesh->mNormals[i].z;
					}
					if (pMesh->mTextureCoords)
					{
						pVertex.TexC.X = pMesh->mTextureCoords[0][i].x;
						pVertex.TexC.Y = pMesh->mTextureCoords[0][i].y;
					}
					pImportMesh.VertexData.push_back(pVertex);
				}
				for (int i = 0; i < pMesh->mNumFaces; i++)
				{
					aiFace face = pMesh->mFaces[i];
					for (int j = 0; j < face.mNumIndices; j++)
						pImportMesh.IndexData.push_back(face.mIndices[j]);
				}
			}

			if (pModel->HasMaterials())
			{
				aiMaterial* pMaterial = pModel->mMaterials[pMesh->mMaterialIndex];
				RAssimpMaterial pAssimpMateria;
				for (int i = 1; i <= 6; i++)
				{
					aiString aistr;
					pMaterial->GetTexture((aiTextureType)i, 0, &aistr);
					std::string pPath = aistr.C_Str();
					if (!(pPath.size() > 1))
						continue;
					pPath = GetFilePath(InName, pPath);
					switch (i)
					{
					case 1:
						pAssimpMateria.DiffuseMapFileName = pPath;
						break;
					case 2:
						pAssimpMateria.SpecularMapFileName = pPath;
						break;
					case 3:
						pAssimpMateria.AmbientMapFileName = pPath;
						break;
					case 6:
						pAssimpMateria.NormalsMapFileName = pPath;
						break;
					default:
						break;
					}

					if (pImportModel.MaterialMap.find(0) == pImportModel.MaterialMap.end())
						pImportModel.MaterialMap.insert(make_pair(0, pAssimpMateria));
				}
			}
		}
	}
	aiImporter.FreeScene();
}