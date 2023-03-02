#include"ClassInspectorMapping.h"
#include"../../Engine/Actor/ActorObject.h"
#include"RegisterInspector.h"
#include"../../Engine/Component/TransformComponent/TransformComponent.h"
void ClassInspectorMapping::UpdateDetailsWidget(RMinimalObject* InCoreMinimalObject)
{

}
/// <summary>
/// 
/// </summary>
/// <param name="InCoreMinimalObject"></param>
void ActorObjectInspectorMapping::UpdateDetailsWidget(RMinimalObject* InRMinimalObject)
{
	if (GActorObject* InActorObject = dynamic_cast<GActorObject*>(InRMinimalObject))
	{
		auto pComponent = dynamic_cast<RComponent*>(InActorObject->GetTransformationComponent());
		if (pComponent)
		{
			ShowPlaceholderObject(pComponent, 0);
		}
	}
}

void ActorObjectInspectorMapping::ShowPlaceholderObject(RComponent* InComponent, int ID)
{
	ImGui::PushID(ID);

	bool bNodeOpen = ImGui::TreeNode(
		InComponent->GetGuidString().c_str(),
		"%s",
		InComponent->GetName().c_str());

	if (bNodeOpen)
	{
		//¸üÐÂWidget
		RegisterInspector::UpdatePropertyWidget(InComponent->GetNativeClass().Property);

		ImGui::TreePop();
	}

	std::vector<RComponent*>& InComponents = InComponent->GetChildrens();
	for (auto& Tmp : InComponents)
	{
		ShowPlaceholderObject(Tmp, ++ID);
	}


	ImGui::PopID();
}

shared_ptr<ClassInspectorMapping> ActorObjectInspectorMapping::MakeDetailsMapping()
{
	return make_shared<ActorObjectInspectorMapping>();
}