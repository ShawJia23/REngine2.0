#include"DXDescriptorHeap.h"
#include"../../Engine/DXRenderEngine.h"
void RDXDescriptorHeap::CreatePSO(UINT numDescriptor)
{
    D3D12_DESCRIPTOR_HEAP_DESC HeapDesc;
    HeapDesc.NumDescriptors = numDescriptor;
    HeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    HeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    HeapDesc.NodeMask = 0;

    DXRenderEngine::getInstance().GetD3dDevice()->CreateDescriptorHeap(&HeapDesc, IID_PPV_ARGS(&m_CBVHeap));
}

void RDXDescriptorHeap::SetDescriptorHeap()
{
	ID3D12DescriptorHeap* DescriptorHeap[] = { m_CBVHeap.Get() };
	DXRenderEngine::getInstance().GetCommandList()->SetDescriptorHeaps(_countof(DescriptorHeap), DescriptorHeap);
}
