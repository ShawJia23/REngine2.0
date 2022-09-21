#pragma once
#include"../Core/RObject/RMinimalObject.h"
#include"DX12/d3dx12.h"
#include "../Core/Engine.h"
#if defined(_WIN32)
#include "../Platform/Windows/WindowsEngine.h"
#else
#endif
class IRenderingInterface
{
	friend class WindowsEngine;
public:
	IRenderingInterface();
	virtual ~IRenderingInterface();

	virtual void Init();

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);
protected:
	ComPtr<ID3D12Resource> ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize);
protected:
	ComPtr<ID3D12Device> GetD3dDevice();
	ComPtr<ID3D12GraphicsCommandList> GetGraphicsCommandList();
	ComPtr<ID3D12CommandAllocator> GetCommandAllocator();
#if defined(_WIN32)
	WindowsEngine* GetEngine();
#else
	FEngine* GetEngine();
#endif
};