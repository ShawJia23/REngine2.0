#include "LogSystem.h"
#include"../../Timer/GameTimer.h"
EditorLogSystem* EditorLogSystem::LogSystem = nullptr;

EditorLogSystem::EditorLogSystem()
{
    bAutoScroll = true;
}

EditorLogSystem* EditorLogSystem::Get()
{
    if (!LogSystem)
    {
        LogSystem = new EditorLogSystem();
    }
    return LogSystem;
}

void EditorLogSystem::Destory()
{
    if (LogSystem)
    {
        delete LogSystem;
        LogSystem = NULL;
    }
}

void EditorLogSystem::Clear()
{
    TextBuff.clear();
    LineOffsets.clear();
    LineOffsets.push_back(0);
}

void EditorLogSystem::AddLog(const char* Fmt, ...)
{
    int TextSize = TextBuff.size();

    va_list Args;
    va_start(Args, Fmt);
    TextBuff.appendfv(Fmt, Args);
    va_end(Args);

    TextBuff.append("\n");

    for (int i = TextBuff.size(); TextSize < i; TextSize++)
    {
        if (TextBuff[TextSize] == '\n')
        {
            LineOffsets.push_back(TextSize + 1);
        }
    }
}

void EditorLogSystem::AddError(const char* Fmt, ...)
{

}

void EditorLogSystem::AddWarning(const char* Fmt, ...)
{

}

void EditorLogSystem::AddSuccess(const char* Fmt, ...)
{

}

void EditorLogSystem::Draw(GameTimer& gt)
{
    if (!ImGui::Begin("Log"))
    {
        ImGui::End();
        return;
    }

    //��ť����
    {
        if (ImGui::BeginPopup("LogOptions"))
        {
            ImGui::Checkbox("Auto Scroll", &bAutoScroll);
            ImGui::EndPopup();
        }

        ImGui::SameLine();

        //��Ҫһ����ť������־
        if (ImGui::Button("LogOptions"))
        {
            ImGui::OpenPopup("LogOptions");
        }

        ImGui::SameLine();

        if (ImGui::Button("ClearAllLog"))
        {
            Clear();
        }

        ImGui::SameLine();

        if (ImGui::Button("CopyAllLog"))
        {
            ImGui::LogToClipboard();
        }

        ImGui::SameLine();

        TextFikter.Draw("LogFilter", -100.0f);
    }

    const char* TextBuffStart = TextBuff.begin();
    const char* TextBuffEnd = TextBuff.end();

    ImGui::Separator();

    ImGui::BeginChild("LogScrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    //��־ɸѡ��
    if (TextFikter.IsActive())
    {
        for (int i = 0; i < LineOffsets.Size; i++)
        {
            const char* LineStart = TextBuffStart + LineOffsets[i];
            const char* LineEnd = (i + 1 < LineOffsets.Size) ? (TextBuffStart + LineOffsets[i + 1] - 1) : TextBuffEnd;

            if (TextFikter.PassFilter(LineStart, LineEnd))
            {
                ImGui::TextUnformatted(LineStart, LineEnd);
            }
        }
    }
    else
    {
        ImGuiListClipper Clipper;
        Clipper.Begin(LineOffsets.Size);
        while (Clipper.Step())
        {
            for (int i = Clipper.DisplayStart; i < Clipper.DisplayEnd; i++)
            {
                const char* LineStart = TextBuffStart + LineOffsets[i];
                const char* LineEnd = (i + 1 < LineOffsets.Size) ? (TextBuffStart + LineOffsets[i + 1] - 1) : TextBuffEnd;;

                ImGui::TextUnformatted(LineStart, LineEnd);
            }
        }

        Clipper.End();
    }

    //�ܿ������µ���־
    if (bAutoScroll &&
        ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();
    ImGui::End();
}
