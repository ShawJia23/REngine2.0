#include "DXDeviceInterface.h"
#include "../Platform/Windows/WindowsEngine.h"
#include"../Manage/MeshManage.h"
#include"../Manage/TextureManage.h"
#include"../World.h"
#include"../Camera/Camera.h"

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

RCamera* IDirectXDeviceInterface::GetCamera() const
{
	if (GetWorld())
	{
		return GetWorld()->GetCamera();
	}

	return nullptr;
}

int IDirectXDeviceInterface::GetViewportWidth()const 
{
	if (GetCamera())
	{
		return GetCamera()->GetWidth();
	}

	return 0;
}
int IDirectXDeviceInterface::GetViewportHeight()const 
{
	if (GetCamera())
	{
		return GetCamera()->GetHeight();
	}
	return 0;
}

RWorld* IDirectXDeviceInterface::GetWorld() const
{
	if (RWindowsEngine* InEngine = GetEngine())
	{
		return InEngine->GetWorld();
	}

	return NULL;
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

RCamera* IDirectXDeviceInterface_Struct::GetCamera() const
{
	return Interface.GetCamera();
}

int IDirectXDeviceInterface_Struct::GetViewportWidth()const
{
	return Interface.GetViewportWidth();
}
int IDirectXDeviceInterface_Struct::GetViewportHeight()const
{
	return Interface.GetViewportHeight();
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