#include "DXDeviceInterface.h"
#include "../Platform/Windows/WindowsEngine.h"
#include"../Manage/MeshManage.h"
#include"../Manage/TextureManage.h"
#include"../World.h"

ComPtr<ID3D12Fence> IDirectXDeviceInterface::GetFence() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetFence();
		}
	}

	return NULL;
}

ComPtr<ID3D12Device> IDirectXDeviceInterface::GetD3dDevice() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetD3dDevice();
		}
	}

	return NULL;
}

ComPtr<ID3D12GraphicsCommandList> IDirectXDeviceInterface::GetCommandList() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetCommandList();
		}
	}

	return NULL;
}

ComPtr<ID3D12CommandAllocator> IDirectXDeviceInterface::GetCommandAllocator() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetCommandAllocator();
		}
	}

	return NULL;
}

ComPtr<ID3D12CommandQueue> IDirectXDeviceInterface::GetCommandQueue() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetCommandQueue();
		}
	}

	return NULL;
}

UINT64 IDirectXDeviceInterface::GetCurrentFenceIndex() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetCurrentFenceIndex();
		}
	}

	return NULL;
}

HWND IDirectXDeviceInterface::GetMianWindowsHandle() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetMainWindowsHandle();
		}
	}

	return HWND();
}

RMeshManage* IDirectXDeviceInterface::GetMeshManage() const
{
	return GetEngine()->GetMeshManage();
}
RTextureManage* IDirectXDeviceInterface::GetTextureManage() const
{
	return GetEngine()->GetTextureManage();
}

RLightManage* IDirectXDeviceInterface::GetLightManage() const
{
	return GetEngine()->GetLightManage();
}

RWorld* IDirectXDeviceInterface::GetWorld() const
{
	if (RWindowsEngine* InEngine = GetEngine())
	{
		return InEngine->GetWorld();
	}

	return NULL;
}


DX12Pipeline* IDirectXDeviceInterface::GetRenderPipeline() const
{
	if (RMeshManage* meshManage = GetMeshManage())
	{
		return meshManage->GetDX12Pipeline();
	}

	return NULL;
}

std::shared_ptr<RenderLayerManage> IDirectXDeviceInterface::GetRenderLayerManage() const
{
	if (DX12Pipeline* pipeline = GetRenderPipeline())
	{
		return pipeline->GetRenderLayer();
	}

	return nullptr;
}

#if defined(_WIN32)
RWindowsEngine* IDirectXDeviceInterface::GetEngine() const
{
	return dynamic_cast<RWindowsEngine*>(Engine);
}
#else
CEngine* IDirectXDeviceInterfece::GetEngine() const
{
	return Engine;
}
#endif


ComPtr<ID3D12Fence> IDirectXDeviceInterface_Struct::GetFence() const
{
	return Interface.GetFence();
}

ComPtr<ID3D12Device> IDirectXDeviceInterface_Struct::GetD3dDevice() const
{
	return Interface.GetD3dDevice();
}

RMeshManage* IDirectXDeviceInterface_Struct::GetMeshManage() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetMeshManage();
		}
	}
	return nullptr;
}

RLightManage* IDirectXDeviceInterface_Struct::GetLightManage() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetLightManage();
		}
	}
	return nullptr;
}

RTextureManage* IDirectXDeviceInterface_Struct::GetTextureManage() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		if (engine->GetRenderEngine())
		{
			return engine->GetRenderEngine()->GetTextureManage();
		}
	}
	return nullptr;
}

RWorld* IDirectXDeviceInterface_Struct::GetWorld() const
{
	return Interface.GetWorld();
}

ComPtr<ID3D12GraphicsCommandList> IDirectXDeviceInterface_Struct::GetCommandList() const
{
	return Interface.GetCommandList();
}

ComPtr<ID3D12CommandAllocator> IDirectXDeviceInterface_Struct::GetCommandAllocator() const
{
	return Interface.GetCommandAllocator();
}

ComPtr<ID3D12CommandQueue> IDirectXDeviceInterface_Struct::GetCommandQueue() const
{
	return Interface.GetCommandQueue();
}

UINT64 IDirectXDeviceInterface_Struct::GetCurrentFenceIndex() const
{
	return Interface.GetCurrentFenceIndex();
}

HWND IDirectXDeviceInterface_Struct::GetMianWindowsHandle() const
{
	return Interface.GetMianWindowsHandle();
}

DX12Pipeline* IDirectXDeviceInterface_Struct::GetRenderPipeline() const
{
	return Interface.GetRenderPipeline();
}

std::shared_ptr<RenderLayerManage> IDirectXDeviceInterface_Struct::GetRenderLayerManage() const
{
	return Interface.GetRenderLayerManage();
}

#if defined(_WIN32)
RWindowsEngine* IDirectXDeviceInterface_Struct::GetEngine() const
{
	return Interface.GetEngine();
}
#else
CEngine* IDirectXDeviceInterface_Struct::GetEngine() const
{
	return Interface.GetEngine();
}
#endif


#if EDITOR_ENGINE
#include"../../Editor/Editor.h"
EditorEngine* IDirectXDeviceInterface::GetEditorEngine() const
{
	if (RWindowsEngine* engine = GetEngine())
	{
		return engine->GetEditorEngine();
	}

	return NULL;
}

EditorEngine* IDirectXDeviceInterface_Struct::GetEditorEngine() const
{
	return Interface.GetEditorEngine();
}
#endif