#include"Editor.h"
#include "../imgui/imgui.h"

EditorEngine::EditorEngine()
{
	m_ToolbarEditor = new ToolbarEditor();
	m_LogEditor = new LogEditor();
	m_ObjectExplorerEditor =new ObjectExplorerEditor();
	m_InspectorEditor = new InspectorEditor();
}

int EditorEngine::PreInit(
#if defined(_WIN32)
	WinMainCommandParameters InParameters
#endif // 1
)
{
	return 0;
}

int EditorEngine::Init(
#if defined(_WIN32)
	WinMainCommandParameters InParameters
#endif
)
{
	return 0;
}

int EditorEngine::PostInit()
{
	return 0;
}

int EditorEngine::PreExit()
{
	return 0;
}

int EditorEngine::Exit()
{
	return 0;
}

int EditorEngine::PostExit()
{
	return 0;
}

void EditorEngine::BuildEditor()
{
	ImGuiIO& IO = ImGui::GetIO();
	IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	m_ToolbarEditor->BuildEditor();
	m_LogEditor->BuildEditor();
	m_ObjectExplorerEditor->BuildEditor();
	m_InspectorEditor->BuildEditor();
}

void EditorEngine::DrawEditor(GameTimer& gt)
{
	DrawLayer(gt);

	m_ToolbarEditor->DrawEditor(gt);
	m_LogEditor->DrawEditor(gt);
	m_ObjectExplorerEditor->DrawEditor(gt);
	m_InspectorEditor->DrawEditor(gt);
}

void EditorEngine::ExitEditor()
{
	m_ToolbarEditor->ExitEditor();
	m_LogEditor->ExitEditor();
	m_ObjectExplorerEditor->ExitEditor();
	m_InspectorEditor->ExitEditor();
}

void EditorEngine::DrawLayer(GameTimer& gt)
{
	ImGuiDockNodeFlags DockspaceFlags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	const ImGuiViewport* Viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(Viewport->WorkPos);
	ImGui::SetNextWindowSize(Viewport->WorkSize);
	ImGui::SetNextWindowViewport(Viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	WindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	WindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	WindowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	//背景改为透明
	DockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

	bool bOpenWindows = true;
	ImGui::Begin("Hell", &bOpenWindows, WindowFlags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);

	ImGuiIO& IO = ImGui::GetIO();
	//是不是开启吸附
	if (IO.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID DockspaceID = ImGui::GetID("EditorEngineLayer");
		ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), DockspaceFlags);
	}

	ImGui::End();

}
