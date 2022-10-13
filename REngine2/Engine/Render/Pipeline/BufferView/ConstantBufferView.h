#pragma once
#include"../../../Interface/DXDeviceInterface.h"
#include"../../ResourcesUpdate.h"
struct RConstantBufferView :public IDirectXDeviceInterface_Struct
{
	void CreateConstant(UINT objectSize, UINT objectCount);

	void Update(int index, const void* data);

	void BuildConstantBuffer(
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle,
		UINT constantBufferNum,
		UINT handleOffset = 0);
protected:
	shared_ptr<ResourcesUpdate> m_Constant;
};