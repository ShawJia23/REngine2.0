#include"ObjectAnalysis.h"
#include"../Mesh/BaseMesh.h"
#include"../Component/RComponentMinimal.h"
#include"../Mesh/SubMesh/MeshGroup.h"
#include "Path/PathHelper.h"
#include <fstream>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

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

ObjectAnalysisByAssimp::ObjectAnalysisByAssimp()
{

}
ObjectAnalysisByAssimp ::~ObjectAnalysisByAssimp()
{
}

void ObjectAnalysisByAssimp::LoadMesh(std::string fileName,std::string name, const XMFLOAT3& newPosition,bool IsRight)
{
	Assimp::Importer aiImporter;
	const aiScene* pModel = aiImporter.ReadFile(fileName, aiProcess_ConvertToLeftHanded);
	if (nullptr == pModel)
	{
		return;
	}
	if (pModel->HasMeshes())
	{
		MeshGroup* pMeshGroup = new MeshGroup();
		for (int num = 0; num < pModel->mNumMeshes; num++)
		{
			aiMesh* pMesh = pModel->mMeshes[num];

			MeshRenderData pMeshData;
			CustomMeshComponent* pMeshComponent = new CustomMeshComponent();
			if (pMesh->HasFaces())
			{
				for (int i = 0; i < pMesh->mNumVertices; i++)
				{
					pMeshData.VertexData.push_back(RVertex(XMFLOAT3(pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z),
						XMFLOAT3(pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z),
						XMFLOAT2(pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y),
						XMFLOAT4(Colors::Red)));
				}
				for (int i = 0; i < pMesh->mNumFaces; i++)
				{
					aiFace face = pMesh->mFaces[i];
					for (int j = 0; j < face.mNumIndices; j++)
						pMeshData.IndexData.push_back(face.mIndices[j]);
				}
				pMeshGroup->AddSubmesh(pMesh->mName.C_Str(), pMeshComponent, pMeshData);
			}

			if (pModel->HasMaterials())
			{
				aiMaterial* pMaterial = pModel->mMaterials[pMesh->mMaterialIndex];
				SetMaterialTex(pMaterial, pMeshGroup, pMesh->mName.C_Str(), name, IsRight);

				aiColor3D ainum;

				pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ainum);
				float a = ainum.r;
			}
		}
		pMeshGroup->SetPosition(newPosition);
		pMeshGroup->CreateMesh();
		pMeshGroup->CreateTexture();
	}
}

void ObjectAnalysisByAssimp::SetMaterialTex(aiMaterial* pMaterial, MeshGroup* pMeshGroup,std::string meshName, std::string ObjName, bool  IsRight)
{
	for (int i = 1; i <= 6; i++) 
	{
		aiString aistr;

		pMaterial->GetTexture((aiTextureType)i, 0, &aistr);
		std::string pPath = aistr.C_Str();

		pMeshGroup->AddTexture(meshName,
			GetTexName(ObjName, pPath),
			GetFilePath(IsRight, ObjName, pPath),
			i);
	}
}

std::string ObjectAnalysisByAssimp::GetFilePath(bool IsRight, std::string ObjName, std::string TexName)
{
	string pTexNamePath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineAssetPath()) + "/Model/";;
	pTexNamePath += ObjName;
	pTexNamePath += "/";
	//路径是正确的
	if (IsRight) 
	{
		if (TexName.size() > 0)
		{
			pTexNamePath += TexName;
			return pTexNamePath;
		}
	}
	else
	{
		auto str1 = StringSplit(TexName, '\\');
		if (str1.size() > 0) 
		{
			TexName = str1.back();
			pTexNamePath += TexName;
			return pTexNamePath;
		}
	}
	return "";
}

std::string ObjectAnalysisByAssimp::GetTexName(std::string ObjName, std::string TexName)
{
	std::string pTexName = ObjName;
	pTexName += "/";
	auto str1 = StringSplit(TexName, '\\');
	if (str1.size() > 0)
	{
		TexName = str1.back();
		pTexName += TexName;
	}
	return pTexName;
}