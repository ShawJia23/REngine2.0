#pragma once
#include"../../ResourcesUpdate.h"
struct RConstantBufferView 
{
	void CreateConstant(UINT objectSize, UINT objectCount,bool bConstBuffer = true);

	void Update(int index, const void* data);

	void BuildConstantBuffer(
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle,
		UINT constantBufferNum,
		UINT handleOffset = 0);

	ID3D12Resource* GetBuffer() { return m_Constant->GetBuffer(); }

	UINT GetConstantBufferByteSize();
protected:
	shared_ptr<ResourcesUpdate> m_Constant;
};