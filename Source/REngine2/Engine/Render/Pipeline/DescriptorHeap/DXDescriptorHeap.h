#pragma once
#include"../../../EngineMinimal.h"
struct RDXDescriptorHeap 
{
	void CreatePSO(UINT numDescriptor);
	void SetDescriptorHeap();
	ID3D12DescriptorHeap* GetHeap()const { return m_CBVHeap.Get(); }
protected:
	ComPtr<ID3D12DescriptorHeap> m_CBVHeap;
};