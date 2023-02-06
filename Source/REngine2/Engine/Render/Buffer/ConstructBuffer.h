#pragma once
#include "../../Engine.h"
#include "../../Interface/DXDeviceInterface.h"

namespace ConstructBuffer
{
	struct RConstructBuffer :public IDirectXDeviceInterface_Struct
	{
		ComPtr<ID3D12Resource> ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize);
	};
}