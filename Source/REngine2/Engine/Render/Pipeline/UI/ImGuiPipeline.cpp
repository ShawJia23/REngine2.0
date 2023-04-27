#include "ImGuiPipeline.h"
#include"../../Engine/DXRenderEngine.h"
#include"../../../../Editor/Editor.h"
#include"../../../Platform/Windows/WindowsEngine.h"
#if EDITOR_ENGINE
#include "../../../../Editor/Editor.h"
#endif // EDITOR_ENGINE

RImGuiPipeline::RImGuiPipeline()
{
}

void RImGuiPipeline::Init(ID3D12DescriptorHeap* heap, UINT offset)
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(RWindowsEngine::getInstance().GetMainWindowsHandle());
	 
	UINT CBVSize= DXRenderEngine::getInstance().GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto pCpu=
		CD3DX12_CPU_DESCRIPTOR_HANDLE(heap->GetCPUDescriptorHandleForHeapStart(), offset, CBVSize);

	auto pGpu =
		CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), offset, CBVSize);

	ImGui_ImplDX12_Init(DXRenderEngine::getInstance().GetD3dDevice().Get(),
		1,DXGI_FORMAT_R8G8B8A8_UNORM, heap,
		pCpu,pGpu);

#if EDITOR_ENGINE
	EditorEngine::getInstance().BuildEditor();
#endif
}

void RImGuiPipeline::Draw(GameTimer& gt)
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	Tick(gt);

	ImGui::Render();

	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), DXRenderEngine::getInstance().GetCommandList().Get());
}

void RImGuiPipeline::Exit()
{
#if EDITOR_ENGINE
	EditorEngine::getInstance().ExitEditor();
#endif
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

void RImGuiPipeline::Tick(GameTimer& gt)
{
#if EDITOR_ENGINE
	EditorEngine::getInstance().DrawEditor(gt);
#endif
}
