#include"InspectorEditor.h"
#include"RegisterInspector.h"
#include"PropertyInspectorMapping.h"
#include"RObject/PropertyObject.h"
#include"../../Engine/Actor/ActorObject.h"
extern GActorObject* SelectedObject;

InspectorEditor::InspectorEditor()
{
	LastSelectedObject = nullptr;
}

void InspectorEditor::BuildEditor()
{
	//±äÁ¿Ó³Éä
	RegisterInspector::RegisterProperty("bool", BoolInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("int", IntInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("float", FloatInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("string", StringInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("map", MapInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("vector", ArrayInspectorMapping::MakeDetailsMapping());
	RegisterInspector::RegisterProperty("fvector_3d", Vector3DInspectorMapping::MakeDetailsMapping());
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
