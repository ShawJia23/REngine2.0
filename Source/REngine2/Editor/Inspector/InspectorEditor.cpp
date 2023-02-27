#include"InspectorEditor.h"
#include"RegisterInspector.h"
#include"PropertyInspectorMapping.h"
#include"ClassInspectorMapping.h"
#include"RObject/PropertyObject.h"
#include"../../Engine/Actor/ActorObject.h"
extern GActorObject* SelectedObject;

InspectorEditor::InspectorEditor()
{
	LastSelectedObject = nullptr;
}

void InspectorEditor::BuildEditor()
{
	//Property
	RegisterInspector::RegisterRProperty("bool", BoolInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("int", IntInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("float", FloatInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("string", StringInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("map", MapInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("vector", ArrayInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("fvector_3d", Vector3DInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterRProperty("XMFLOAT3", Vector3DInspectorMapping::MakeDetailsMapping());
	
	//class 
	RegisterInspector::RegisterRClass("GActorObject", ActorObjectInspectorMapping::MakeDetailsMapping());
}

void InspectorEditor::DrawEditor(float DeltaTime)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	ImGui::Begin("DetailsEditor");

	if (SelectedObject)
	{
		if (SelectedObject == LastSelectedObject)
		{
			string ComponentAreaName = SelectedObject->GetName().append(":Component Area");
			if (ImGui::CollapsingHeader(ComponentAreaName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				//映射对象
				RegisterInspector::UpdateClassWidget(SelectedObject);
			}
			if (SelectedObject->GetNativeClass().Property)
			{
				string PropertyAreaName = SelectedObject->GetName().append(":Property Area");
				if (ImGui::CollapsingHeader(PropertyAreaName.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
				{
					//映射变量
					RegisterInspector::UpdatePropertyWidget(SelectedObject->GetNativeClass().Property);
				}
			}
			

			ImGui::Separator();
		}
	}

	ImGui::End();

	LastSelectedObject = SelectedObject;
}

void InspectorEditor::ExitEditor()
{
}
