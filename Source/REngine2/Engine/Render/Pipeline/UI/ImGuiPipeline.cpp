#include "ImGuiPipeline.h"

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

	ImGui_ImplWin32_Init(GetMianWindowsHandle());
	 
	UINT CBVSize= GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	auto pCpu=
		CD3DX12_CPU_DESCRIPTOR_HANDLE(heap->GetCPUDescriptorHandleForHeapStart(), offset, CBVSize);

	auto pGpu =
		CD3DX12_GPU_DESCRIPTOR_HANDLE(heap->GetGPUDescriptorHandleForHeapStart(), offset, CBVSize);

	ImGui_ImplDX12_Init(GetD3dDevice().Get(),
		1,DXGI_FORMAT_R8G8B8A8_UNORM, heap,
		pCpu,pGpu);

#if EDITOR_ENGINE
	GetEditorEngine()->BuildEditor();
#endif
}

void RImGuiPipeline::Draw(GameTimer& gt)
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	Tick(gt);

	ImGui::Render();

	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), GetCommandList().Get());
}

void RImGuiPipeline::Exit()
{
#if EDITOR_ENGINE
	GetEditorEngine()->ExitEditor();
#endif
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

void RImGuiPipeline::Tick(GameTimer& gt)
{
#if EDITOR_ENGINE
	GetEditorEngine()->DrawEditor(gt);
#endif
}
