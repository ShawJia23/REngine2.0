#include "ToolbarEditor.h"
#include"../Editor.h"
void ToolbarEditor::BuildEditor()
{

}

void ToolbarEditor::DrawEditor(float DeltaTime)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();
		}
		ImGui::Separator();

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "ctrl+z"))
			{

			}

			ImGui::EndMenu();
		}

		ImGui::Separator();
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Exploer"))
			{

			}

			if (ImGui::MenuItem("Inspector"))
			{

			}

			if (ImGui::MenuItem("Log"))
			{

			}

			ImGui::EndMenu();
		}

		ImGui::Separator();

		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
}

void ToolbarEditor::ExitEditor()
{

}
