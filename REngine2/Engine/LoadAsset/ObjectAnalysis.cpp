#include"ObjectAnalysis.h"
#include"../Mesh/BaseMesh.h"
#include"../Component/RComponentMinimal.h"
#include <fstream>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

ObjectAnalysisByAssimp::ObjectAnalysisByAssimp()
{

}
ObjectAnalysisByAssimp ::~ObjectAnalysisByAssimp()
{
}

void ObjectAnalysisByAssimp::LoadMesh(std::string fileName,std::string name)
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
				aiString aistr;
				std::string pTexNamePath = "Asset/Model/";
				pTexNamePath += name;
				pTexNamePath += "/";
				pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aistr);
				std::string pTexPath = aistr.C_Str();
				if (pTexPath.size() > 0)
				{
					pTexNamePath += pTexPath;
					std::string pTexName = name;
					pTexName+= "/";
					pTexName += pTexPath;
					pMeshGroup->AddTexture(pMesh->mName.C_Str(), pTexName, pTexNamePath);
				}
			}
		}
		pMeshGroup->CreateMesh();
		pMeshGroup->CreateTexture();
	}
}