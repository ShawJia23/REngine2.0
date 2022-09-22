#pragma once
#include "../Core/Engine.h"

#if defined(_WIN32)
class RWindowsEngine;
#else
class REngine;
#endif

//�ṩ��Ⱦ���ݵĽӿ�
class IDirectXDeviceInterface
{
public:
	ComPtr<ID3D12Fence> GetFence();
	ComPtr<ID3D12Device> GetD3dDevice();

	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator();
	ComPtr<ID3D12CommandQueue> GetCommandQueue();

	UINT64 GetCurrentFenceIndex();
	HWND GetMianWindowsHandle();

#if defined(_WIN32)
	RWindowsEngine* GetEngine();
#else
	CEngine* GetEngine();
#endif
};

//�ṩ��Ⱦ���ݵĽӿ�
struct IDirectXDeviceInterface_Struct
{
public:
	ComPtr<ID3D12Fence> GetFence();
	ComPtr<ID3D12Device> GetD3dDevice();

	ComPtr<ID3D12GraphicsCommandList> GetCommandList();
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator();
	ComPtr<ID3D12CommandQueue> GetCommandQueue();

	UINT64 GetCurrentFenceIndex();
	HWND GetMianWindowsHandle();

#if defined(_WIN32)
	RWindowsEngine* GetEngine();
#else
	REngine* GetEngine();
#endif

private:
	IDirectXDeviceInterface Interfece;
};