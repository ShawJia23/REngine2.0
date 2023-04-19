#include"ObjectExplorer.h"
#include"../../Engine/World.h"
#include"../../Engine/Actor/ActorObject.h"
#include"../../Engine/Render/Pipeline/DX12Pipeline.h"
#include"../OperationHandle/OperationHandleManage.h"
#include"../../Engine/Manage/MeshManage.h"
void ObjectExplorerEditor::BuildEditor()
{
}

extern int SelectedVariable;
void ObjectExplorerEditor::DrawEditor(GameTimer& gt)
{
	if (!bOpen)
		return;
	ImGui::Begin("Object", &bOpen);
	if (RWorld* world = GetWorld())
	{
		auto Actors = world->GetActors();
		for (int i = 0; i < Actors.size(); i++)
		{
			char ObjectNameString[128] = { 0 };
			sprintf(ObjectNameString, "%s_%d",Actors[i]->GetName().c_str(), i);

			if (ImGui::Selectable(ObjectNameString, SelectedVariable == i))
			{
				HighlightDisplayObject(Actors[i]);
				//设置选择对象
				OperationHandleManage::Get()->SetNewSelectedObject(Actors[i]);

				//显示操作手柄
				OperationHandleManage::Get()->DisplaySelectedOperationHandle();
			}
		}
	}
	ImGui::End();
}

void ObjectExplorerEditor::ExitEditor()
{
}

void ObjectExplorerEditor::HighlightDisplayObject(GActorObject* actor)
{
	std::shared_ptr<RenderLayerManage> layer = RMeshManage::getInstance().GetDX12Pipeline()->GetGeometryMap().GetRenderLayerManage();
	
	if (layer.get());
	{
		auto pObject= RMeshManage::getInstance().GetDX12Pipeline()->GetGeometryMap().GetRGeometry(0).FindRenderData(actor);
		if(!pObject.expired())
			layer->HighlightDisplayObject(pObject);
	}
}
