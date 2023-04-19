#pragma once
#include "../Engine.h"

#if defined(_WIN32)
class RWindowsEngine;
#else
class REngine;
#endif

class RWorld;
class DX12Pipeline;
class RenderLayerManage;
class RCamera;
//�ṩ��Ⱦ���ݵĽӿ�
class IDirectXDeviceInterface
{
public:
	ComPtr<ID3D12Fence> GetFence() const;
	ComPtr<ID3D12Device> GetD3dDevice() const;
	RWorld* GetWorld() const;
	RCamera* GetCamera() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMianWindowsHandle() const;

	int GetViewportWidth()const;
	int GetViewportHeight()const;

#if defined(_WIN32)
	RWindowsEngine* GetEngine()  const;
#else
	CEngine* GetEngine();
#endif

#if EDITOR_ENGINE
	class EditorEngine* GetEditorEngine()  const;
#endif 
};

//�ṩ��Ⱦ���ݵĽӿ�
struct IDirectXDeviceInterface_Struct
{
public:
	ComPtr<ID3D12Fence> GetFence() const;
	ComPtr<ID3D12Device> GetD3dDevice() const;
	RWorld* GetWorld() const;
	RCamera* GetCamera() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMianWindowsHandle() const;

	int GetViewportWidth()const;
	int GetViewportHeight()const;

#if defined(_WIN32)
	RWindowsEngine* GetEngine() const;
#else
	REngine* GetEngine();
#endif
#if EDITOR_ENGINE
	class EditorEngine* GetEditorEngine() const;
#endif 
private:
	IDirectXDeviceInterface Interface;
};