#include "LogEditor.h"
#include "LogSystem.h"

void LogEditor::BuildEditor()
{

}

void LogEditor::DrawEditor(float DeltaTime)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

	bool bOpenLog = true;
	ImGui::Begin("Log", &bOpenLog);

	//ImGui::Text("xxxx");

	ImGui::End();

	//»æÖÆ×ÖÌå
	EditorLogSystem::Get()->Draw(DeltaTime);
}

void LogEditor::ExitEditor()
{
	EditorLogSystem::Destory();
}