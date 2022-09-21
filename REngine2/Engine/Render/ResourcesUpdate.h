#pragma once
#include"../EngineMinimal.h"

class ResourcesUpdate :public enable_shared_from_this<ResourcesUpdate>
{
public:
	ResourcesUpdate();
	~ResourcesUpdate();

	void Init(ID3D12Device* device, UINT elemetSize, UINT elemetCount);

	void Update(int index, const void* data);

	UINT GetConstantBufferByteSize(UINT typeSzie);
	UINT GetConstantBufferByteSize();

	ID3D12Resource* GetBuffer() { return m_UploadBuffer.Get(); }
private:
	ComPtr<ID3D12Resource> m_UploadBuffer;
	UINT m_elementSize;
	BYTE* m_data;
};
