#pragma once
#include "../../Engine.h"
#include"../DX12/d3dx12.h"
namespace ConstructBuffer
{
	struct RConstructBuffer 
	{
		ComPtr<ID3D12Resource> ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize);
	};
}