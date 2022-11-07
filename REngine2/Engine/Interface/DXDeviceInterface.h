#pragma once
#include "../Core/Engine.h"

#if defined(_WIN32)
class RWindowsEngine;
#else
class REngine;
#endif

class RLightManage;
class RMeshManage;
class RTextureManage;
class RWorld;
//提供渲染内容的接口
class IDirectXDeviceInterface
{
public:
	ComPtr<ID3D12Fence> GetFence();
	ComPtr<ID3D12Device> GetD3dDevice();
	RMeshManage* GetMeshManage();
	RTextureManage* GetTextureManage();
	RLightManage* GetLightManage();
	RWorld* GetWorld();

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

//提供渲染内容的接口
struct IDirectXDeviceInterface_Struct
{
public:
	ComPtr<ID3D12Fence> GetFence();
	ComPtr<ID3D12Device> GetD3dDevice();
	RMeshManage* GetMeshManage();
	RLightManage* GetLightManage();
	RTextureManage* GetTextureManage();
	RWorld* GetWorld();

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