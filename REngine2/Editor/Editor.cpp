#include"Editor.h"
#include "../imgui/imgui.h"

EditorEngine::EditorEngine()
{
	m_ToolbarEditor = new ToolbarEditor();
	m_LogEditor = new LogEditor();
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
}

void EditorEngine::DrawEditor(float DeltaTime)
{
	DrawLayer(DeltaTime);

	//bool show_demo_window = true;
	//ImGui::ShowDemoWindow(&show_demo_window);//学习案例

	//ImGui::Begin("XXX");
	//ImGui::Text("ASDAASDASDASD");
	//ImGui::End();

	m_ToolbarEditor->DrawEditor(DeltaTime);
	m_LogEditor->DrawEditor(DeltaTime);
}

void EditorEngine::ExitEditor()
{
	m_ToolbarEditor->ExitEditor();
	m_LogEditor->ExitEditor();
}

void EditorEngine::DrawLayer(float DeltaTime)
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
