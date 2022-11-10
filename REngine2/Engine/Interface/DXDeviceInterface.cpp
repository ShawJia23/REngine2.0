#include "DXDeviceInterface.h"
#include "../Platform/Windows/WindowsEngine.h"
#include"../Manage/MeshManage.h"
#include"../LoadAsset/Texture.h"
#include"../Core/World.h"

ComPtr<ID3D12Fence> IDirectXDeviceInterface::GetFence()
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

ComPtr<ID3D12Device> IDirectXDeviceInterface::GetD3dDevice()
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

ComPtr<ID3D12GraphicsCommandList> IDirectXDeviceInterface::GetCommandList()
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

ComPtr<ID3D12CommandAllocator> IDirectXDeviceInterface::GetCommandAllocator()
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

ComPtr<ID3D12CommandQueue> IDirectXDeviceInterface::GetCommandQueue()
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

UINT64 IDirectXDeviceInterface::GetCurrentFenceIndex()
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

HWND IDirectXDeviceInterface::GetMianWindowsHandle()
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

RMeshManage* IDirectXDeviceInterface::GetMeshManage()
{
	return GetEngine()->GetMeshManage();
}
RTextureManage* IDirectXDeviceInterface::GetTextureManage()
{
	return GetEngine()->GetTextureManage();
}
RLightManage* IDirectXDeviceInterface::GetLightManage()
{
	return GetEngine()->GetLightManage();
}

RWorld* IDirectXDeviceInterface::GetWorld()
{
	if (RWindowsEngine* InEngine = GetEngine())
	{
		return InEngine->GetWorld();
	}

	return NULL;
}


#if defined(_WIN32)
RWindowsEngine* IDirectXDeviceInterface::GetEngine()
{
	return dynamic_cast<RWindowsEngine*>(Engine);
}
#else
CEngine* IDirectXDeviceInterfece::GetEngine()
{
	return Engine;
}
#endif


ComPtr<ID3D12Fence> IDirectXDeviceInterface_Struct::GetFence()
{
	return Interfece.GetFence();
}

ComPtr<ID3D12Device> IDirectXDeviceInterface_Struct::GetD3dDevice()
{
	return Interfece.GetD3dDevice();
}

RMeshManage* IDirectXDeviceInterface_Struct::GetMeshManage()
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

RLightManage* IDirectXDeviceInterface_Struct::GetLightManage()
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

RTextureManage* IDirectXDeviceInterface_Struct::GetTextureManage()
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

RWorld* IDirectXDeviceInterface_Struct::GetWorld()
{
	return Interfece.GetWorld();
}

ComPtr<ID3D12GraphicsCommandList> IDirectXDeviceInterface_Struct::GetCommandList()
{
	return Interfece.GetCommandList();
}

ComPtr<ID3D12CommandAllocator> IDirectXDeviceInterface_Struct::GetCommandAllocator()
{
	return Interfece.GetCommandAllocator();
}

ComPtr<ID3D12CommandQueue> IDirectXDeviceInterface_Struct::GetCommandQueue()
{
	return Interfece.GetCommandQueue();
}

UINT64 IDirectXDeviceInterface_Struct::GetCurrentFenceIndex()
{
	return Interfece.GetCurrentFenceIndex();
}

HWND IDirectXDeviceInterface_Struct::GetMianWindowsHandle()
{
	return Interfece.GetMianWindowsHandle();
}

#if defined(_WIN32)
RWindowsEngine* IDirectXDeviceInterface_Struct::GetEngine()
{
	return Interfece.GetEngine();
}
#else
CEngine* IDirectXDeviceInterface_Struct::GetEngine()
{
	return Interfece.GetEngine();
}
#endif