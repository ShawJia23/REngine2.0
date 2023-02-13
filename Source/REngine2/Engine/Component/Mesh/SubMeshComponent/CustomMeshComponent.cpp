#include"CustomMeshComponent.h"
#include"../../../Mesh/MeshType.h"

CustomMeshComponent::CustomMeshComponent()
{

}

void CustomMeshComponent::CreateMesh(MeshRenderData& MeshData, const string& name)
{

}

void CustomMeshComponent::BuildKey(size_t& outKey, const string& name)
{
	std::hash<string> floatHash;

	outKey = 6;
	outKey += floatHash(name);
}
