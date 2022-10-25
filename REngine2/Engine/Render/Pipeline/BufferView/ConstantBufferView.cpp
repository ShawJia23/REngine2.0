#include"ConstantBufferView.h"

void RConstantBufferView::CreateConstant(UINT objectSize, UINT objectCount)
{
    m_Constant = make_shared<ResourcesUpdate>();
    m_Constant->Init(GetD3dDevice().Get(), objectSize, objectCount);
}

void RConstantBufferView::Update(int index, const void* data)
{
   m_Constant->Update(index, data);
}

void RConstantBufferView::BuildConstantBuffer(
    CD3DX12_CPU_DESCRIPTOR_HANDLE handle,
    UINT constantBufferNum,
    UINT handleOffset)
{
    UINT DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    D3D12_GPU_VIRTUAL_ADDRESS Addr = m_Constant->GetBuffer()->GetGPUVirtualAddress();

    for (int i = 0; i < constantBufferNum; i++)
    {
        CD3DX12_CPU_DESCRIPTOR_HANDLE Handle = handle;

        D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc;
        CBVDesc.BufferLocation = Addr + i * m_Constant->GetConstantBufferByteSize();
        CBVDesc.SizeInBytes = m_Constant->GetConstantBufferByteSize();

        Handle.Offset(i + handleOffset, DescriptorOffset);

        GetD3dDevice()->CreateConstantBufferView(&CBVDesc, Handle);
    }
}