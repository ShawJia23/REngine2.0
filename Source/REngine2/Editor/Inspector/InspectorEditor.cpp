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
	RegisterInspector::RegisterRClass("GActorObject", ClassInspectorMapping::MakeDetailsMapping());
}

void InspectorEditor::DrawEditor(float DeltaTime)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	ImGui::Begin("DetailsEditor");

	if (SelectedObject)
	{
		if (SelectedObject == LastSelectedObject)
		{
			ImGui::Separator();
			RPropertyObject* InProperty = SelectedObject->GetNativeClass().Property;
			while (InProperty)
			{
				auto iterator = RegisterInspector::PropertyMappings.find(InProperty->GetType());
				if (iterator != RegisterInspector::PropertyMappings.end())
				{
					iterator->second->UpdateDetailsWidget(InProperty);
				}

				InProperty = dynamic_cast<RPropertyObject*>(InProperty->Nest);
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
