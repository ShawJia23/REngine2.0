#include "Render.h"
#include "../Debug/EngineLog.h"

vector<IRenderingInterface*> IRenderingInterface::RenderingInterface;

IRenderingInterface::IRenderingInterface()
{
	RenderingInterface.push_back(this);
}

IRenderingInterface::~IRenderingInterface()
{
	for (vector<IRenderingInterface*>::const_iterator Iter = RenderingInterface.begin();
		Iter != RenderingInterface.end();
		++Iter)
	{
		if (*Iter == this)
		{
			RenderingInterface.erase(Iter);
			break;
		}
	}
}

void IRenderingInterface::Init()
{
}

void IRenderingInterface::PreDraw(float DeltaTime)
{
	//重值我们的命令列表
	ANALYSIS_HRESULT(GetGraphicsCommandList()->Reset(GetCommandAllocator().Get(), NULL));
}

void IRenderingInterface::Draw(float DeltaTime)
{

}

void IRenderingInterface::PostDraw(float DeltaTime)
{
}

ComPtr<ID3D12Resource> IRenderingInterface::ConstructDefaultBuffer(
	ComPtr<ID3D12Resource>& OutTmpBuffer,
	const void* InData, UINT64 InDataSize)
{
	ComPtr<ID3D12Resource> Buffer;

	CD3DX12_RESOURCE_DESC BufferResourceDESC = CD3DX12_RESOURCE_DESC::Buffer(InDataSize);
	CD3DX12_HEAP_PROPERTIES BufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	ANALYSIS_HRESULT(GetD3dDevice()->CreateCommittedResource(
		&BufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_COMMON,
		NULL, IID_PPV_ARGS(Buffer.GetAddressOf())));

	CD3DX12_HEAP_PROPERTIES UpdateBufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	ANALYSIS_HRESULT(GetD3dDevice()->CreateCommittedResource(
		&UpdateBufferProperties,
		D3D12_HEAP_FLAG_NONE,
		&BufferResourceDESC,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		NULL, IID_PPV_ARGS(OutTmpBuffer.GetAddressOf())));

	D3D12_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pData = InData;
	SubResourceData.RowPitch = InDataSize;
	SubResourceData.SlicePitch = SubResourceData.RowPitch;

	//标记资源为复制目标
	CD3DX12_RESOURCE_BARRIER CopyDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(Buffer.Get(),
		D3D12_RESOURCE_STATE_COMMON,
		D3D12_RESOURCE_STATE_COPY_DEST);

	GetGraphicsCommandList()->ResourceBarrier(1, &CopyDestBarrier);

	//更新子资源，应该填充所有子资源数组
	UpdateSubresources<1>(
		GetGraphicsCommandList().Get(),
		Buffer.Get(),
		OutTmpBuffer.Get(),
		0,//0 -> D3D12_REQ_SUBRESOURCES
		0,//0 -> D3D12_REQ_SUBRESOURCES
		1,
		&SubResourceData);

	CD3DX12_RESOURCE_BARRIER ReadDestBarrier = CD3DX12_RESOURCE_BARRIER::Transition(Buffer.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST,
		D3D12_RESOURCE_STATE_GENERIC_READ);

	return Buffer;
}

ComPtr<ID3D12Device> IRenderingInterface::GetD3dDevice()
{
	if (WindowsEngine* engine = GetEngine())
	{
		return engine->D3dDevice;
	}

	return NULL;
}

ComPtr<ID3D12GraphicsCommandList> IRenderingInterface::GetGraphicsCommandList()
{
	if (WindowsEngine* engine = GetEngine())
	{
		return engine->m_commandList;
	}

	return NULL;
}

ComPtr<ID3D12CommandAllocator> IRenderingInterface::GetCommandAllocator()
{
	if (WindowsEngine* engine = GetEngine())
	{
		return engine->m_commandAllocator;
	}

	return NULL;
}

#if defined(_WIN32)
WindowsEngine* IRenderingInterface::GetEngine()
{
	return dynamic_cast<WindowsEngine*>(Engine);
}
#else
FEngine* IRenderingInterface::GetEngine()
{
	return Engine;
}
#endif