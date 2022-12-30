#include "ToolbarEditor.h"

void ToolbarEditor::BuildEditor()
{

}

void ToolbarEditor::DrawEditor(float DeltaTime)
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Level"))
			{
				NewLevel();
			}

			if (ImGui::MenuItem("Open Level"))
			{

			}

			if (ImGui::MenuItem("Open Asset"))
			{

			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "ctrl+z"))
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

void ToolbarEditor::NewLevel()
{

}
