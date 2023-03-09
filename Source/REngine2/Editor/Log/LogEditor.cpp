#include "LogEditor.h"
#include "LogSystem.h"

void LogEditor::BuildEditor()
{
}

void LogEditor::DrawEditor(GameTimer& gt)
{
	if (!bOpen)
		return;
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	ImGui::Begin("Log", &bOpen);

	//ImGui::Text("xxxx");

	ImGui::End();

	//»æÖÆ×ÖÌå
	EditorLogSystem::Get()->Draw(gt);
}

void LogEditor::ExitEditor()
{
	EditorLogSystem::Destory();
}

void LogEditor::RenderEnd() 
{
	EditorBase::RenderEnd();
}