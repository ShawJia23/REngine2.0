#include"CustomMeshComponent.h"
#include"../../../Mesh/MeshType.h"
#include "FBXSDK.h"
#pragma comment(lib, "AssetImport.lib")
#include"../../../EngineMinimal.h"

CustomMeshComponent::CustomMeshComponent()
{

}

void CustomMeshComponent::CreateMesh(MeshRenderData& MeshData, const string& name)
{
	char Buff[1024] = { 0 };
	get_path_clean_filename(Buff, name.c_str());

	char PathBuff[1024] = { 0 };
	get_full_path(PathBuff, 1024, name.c_str());

	LoadFBXFromBuff(MeshData, PathBuff);
}

void CustomMeshComponent::BuildKey(size_t& outKey, const string& name)
{
	std::hash<string> floatHash;

	outKey = 6;
	outKey += floatHash(name);
}

bool CustomMeshComponent::LoadFBXFromBuff(MeshRenderData& MeshData, const string& inName)
{
	RFBXRenderData RenderData;
	RFBXAssetImport().LoadMeshData(inName.c_str(), RenderData);
	
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