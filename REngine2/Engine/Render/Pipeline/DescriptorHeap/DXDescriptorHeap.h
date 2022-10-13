#pragma once
#include"../../../Interface/DXDeviceInterface.h"

struct RDXDescriptorHeap :public IDirectXDeviceInterface_Struct
{
	void Build(UINT numDescriptor);
	void SetDescriptorHeap();
	ID3D12DescriptorHeap* GetHeap()const { return m_CBVHeap.Get(); }
protected:
	ComPtr<ID3D12DescriptorHeap> m_CBVHeap;
};