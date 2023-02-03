#include"ObjectExplorer.h"
#include"../../Engine/World.h"
#include"../../Engine/Actor/ActorObject.h"
#include"../../Engine/Render/Pipeline/DX12Pipeline.h"
void ObjectExplorerEditor::BuildEditor()
{
}

extern int SelectedVariable;
void ObjectExplorerEditor::DrawEditor(float DeltaTime)
{
	ImGui::Begin("Object");
	if (RWorld* world = GetWorld())
	{
		ImGui::BeginChild("Object Panel", ImVec2(150, 0), true);

		const vector<GActorObject*> Actors = world->GetActors();
		for (int i = 0; i < Actors.size(); i++)
		{
			char ObjectNameString[128] = { 0 };
			sprintf(ObjectNameString, "%s_%d",Actors[i]->GetName().c_str(), i);

			if (ImGui::Selectable(ObjectNameString, SelectedVariable == i))
			{
				HighlightDisplayObject(Actors[i]);
			}
		}

		ImGui::EndChild();

	}
	ImGui::End();
}

void ObjectExplorerEditor::ExitEditor()
{
}

void ObjectExplorerEditor::HighlightDisplayObject(GActorObject* actor)
{
	if (std::shared_ptr<RenderLayerManage> layer = GetRenderLayerManage())
	{
		auto pObject=GetRenderPipeline()->GetGeometryMap().GetRGeometry(0).FindRenderData(actor);
		if(!pObject.expired())
			layer->HighlightDisplayObject(pObject);
	}
}
