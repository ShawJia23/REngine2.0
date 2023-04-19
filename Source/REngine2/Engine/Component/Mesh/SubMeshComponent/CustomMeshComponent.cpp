#include"CustomMeshComponent.h"
#include"../../../Mesh/MeshType.h"
#pragma comment(lib, "AssetImport.lib")
#include "ImportSDK.h"
#include"../../../EngineMinimal.h"

CustomMeshComponent::CustomMeshComponent()
{

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

void CustomMeshComponent::CreateMesh(MeshRenderData& meshData, const string& name, MeshRenderData& inData)
{
	auto str1 = StringSplit(name, '.');
	if (str1.size() > 1 && strcmp("fbx",str1.back().c_str())==0)
	{
		//LoadFBXFromBuff(meshData, name.c_str());
	}
	else
	{
		meshData.VertexData = inData.VertexData;
		meshData.IndexData = inData.IndexData;
	}

}

void CustomMeshComponent::BuildKey(size_t& outKey, const string& name, MeshRenderData& inData)
{
	std::hash<string> floatHash;

	outKey = 6;
	outKey += floatHash(name);
}

bool CustomMeshComponent::LoadFBXFromBuff(MeshRenderData& MeshData, const string& inName)
{
	RImportRenderData RenderData;
	RAssetImport().LoadMeshData(inName.c_str(), RenderData);
	
	for (auto& TmpModel : RenderData.ModelData)
	{
		for (auto& MeshTmp : TmpModel.MeshData)
		{
			for (auto& VertexTmp : MeshTmp.VertexData)
			{
				for (int i = 0; i < 3; i++)
				{
					MeshData.VertexData.push_back(RVertex());
					RVertex& InVertex = MeshData.VertexData.back();

					InVertex.Position.x = VertexTmp.Vertexs[i].Position.X;
					InVertex.Position.y = VertexTmp.Vertexs[i].Position.Y;
					InVertex.Position.z = VertexTmp.Vertexs[i].Position.Z;

					InVertex.Normal.x = VertexTmp.Vertexs[i].Normal.X;
					InVertex.Normal.y = VertexTmp.Vertexs[i].Normal.Y;
					InVertex.Normal.z = VertexTmp.Vertexs[i].Normal.Z;

					InVertex.TangentU.x = VertexTmp.Vertexs[i].Tangent.X;
					InVertex.TangentU.y = VertexTmp.Vertexs[i].Tangent.Y;
					InVertex.TangentU.z = VertexTmp.Vertexs[i].Tangent.Z;

					InVertex.TexC.x = VertexTmp.Vertexs[i].UV.X;
					InVertex.TexC.y = VertexTmp.Vertexs[i].UV.Y;
				}
			}

			//¿½±´
			MeshData.IndexData = MeshTmp.IndexData;
		}
	}
	return true;
}
