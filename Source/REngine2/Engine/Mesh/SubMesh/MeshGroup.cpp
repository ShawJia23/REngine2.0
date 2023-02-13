#include "MeshGroup.h"
#include"CustomMesh.h"
#include"../../Component/Mesh/SubMeshComponent/CustomMeshComponent.h"
#include"../../World.h"
#include"../../Manage/MeshManage.h"
#include"../../Manage/TextureManage.h"
MeshGroup::MeshGroup()
{
	m_RenderDatas.clear();
}

void MeshGroup::SetPosition(const XMFLOAT3& newPosition) 
{
	for (auto& Tmp : m_RenderDatas)
	{
		Tmp.second.Mesh->SetPosition(newPosition);
	}
}

void MeshGroup::AddSubmesh(std::string name, RMeshComponent* mesh, MeshRenderData MeshData)
{
	if (m_RenderDatas.find(name) != m_RenderDatas.end())
	{
		name = name + "1";
	}
	size_t hashKey = 0;
	dynamic_cast<CustomMeshComponent*>(mesh)->BuildKey(hashKey, name);
	CustomMesh* pCustomMesh=GetWorld()->CreateActorObject<CustomMesh>();
	if (pCustomMesh)
	{
		mesh->Rename("CustomComponent");
		mesh->SetOuter(pCustomMesh);
		pCustomMesh->SetMeshComponent(mesh);
		pCustomMesh->Rename(name);
	}
	SubMesh pSubMesh;
	pSubMesh.Mesh = pCustomMesh;
	pSubMesh.MeshData.IndexData = MeshData.IndexData;
	pSubMesh.MeshData.VertexData = MeshData.VertexData;
	pSubMesh.outKey = hashKey;
	m_RenderDatas[name] = pSubMesh;
}

void MeshGroup::CreateMesh()
{
	for (auto Tmp :m_RenderDatas) 
	{
		GetMeshManage()->CreateMeshGroup(Tmp.second.outKey,Tmp.second.Mesh->GetMeshComponent(), Tmp.second.MeshData);
	}
}

void MeshGroup::AddTexture(std::string objName, std::string texName, std::string fileName, int type) 
{
	if (texName.empty() || fileName.empty())
		return;
	GetTextureManage()->LoadTextureFormPath(texName, fileName);

	if (m_RenderDatas.find(objName) != m_RenderDatas.end())
	{
		auto Tmp = m_RenderDatas[objName].Mesh;
		if (RMaterial* pMaterial = (*Tmp->GetMaterials())[0])
		{
			switch (type)
			{
			case 1:
				pMaterial->SetBaseColorIndexKey(texName);
				break;
			case 2:
				pMaterial->SetSpecularIndexKey(texName);
				break;
			case 6:
				pMaterial->SetNormalIndexKey(texName);
				break;
			default:
				break;
			}
			pMaterial->SetRoughness(0.8f);
		}
	}
}
void MeshGroup::CreateTexture()
{
	GetTextureManage()->CreateTexture();
}

MeshGroup::SubMesh::SubMesh():
	Mesh(NULL)
{
}
