#pragma once
#include "../Engine.h"

#if defined(_WIN32)
class RWindowsEngine;
#else
class REngine;
#endif

class RLightManage;
class RMeshManage;
class RTextureManage;
class RWorld;
class DX12Pipeline;
class RenderLayerManage;
//�ṩ��Ⱦ���ݵĽӿ�
class IDirectXDeviceInterface
{
public:
	ComPtr<ID3D12Fence> GetFence() const;
	ComPtr<ID3D12Device> GetD3dDevice() const;
	RMeshManage* GetMeshManage() const;
	RTextureManage* GetTextureManage() const;
	RLightManage* GetLightManage() const;
	RWorld* GetWorld() const;
	DX12Pipeline* GetRenderPipeline() const;
	std::shared_ptr<RenderLayerManage> GetRenderLayerManage() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMianWindowsHandle() const;

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
	RMeshManage* GetMeshManage() const;
	RLightManage* GetLightManage() const;
	RTextureManage* GetTextureManage() const;
	RWorld* GetWorld() const;
	DX12Pipeline* GetRenderPipeline() const;
	std::shared_ptr<RenderLayerManage> GetRenderLayerManage() const;

	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const;
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator() const;
	ComPtr<ID3D12CommandQueue> GetCommandQueue() const;

	UINT64 GetCurrentFenceIndex() const;
	HWND GetMianWindowsHandle() const;

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