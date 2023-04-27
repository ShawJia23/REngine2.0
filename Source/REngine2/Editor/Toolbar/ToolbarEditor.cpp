#include "ToolbarEditor.h"
#include"../Editor.h"

void ToolbarEditor::BuildEditor()
{
}

void ToolbarEditor::DrawEditor(GameTimer& gt)
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
				EditorEngine::getInstance().m_ObjectExplorerEditor->RenderStart();
			}

			if (ImGui::MenuItem("Inspector"))
			{
				EditorEngine::getInstance().m_InspectorEditor->RenderStart();
			}

			if (ImGui::MenuItem("Log"))
			{
				EditorEngine::getInstance().m_LogEditor->RenderStart();
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
