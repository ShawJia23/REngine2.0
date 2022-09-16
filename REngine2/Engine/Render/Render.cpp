#include "Render.h"
#include "../Debug/EngineLog.h"
#include "../Platform/Windows/WindowsEngine.h"

vector<IRenderingInterface*> IRenderingInterface::RenderingInterface;

IRenderingInterface::IRenderingInterface()
{
	create_guid(&Guid);

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
		return engine->GraphicsCommandList;
	}

	return NULL;
}

ComPtr<ID3D12CommandAllocator> IRenderingInterface::GetCommandAllocator()
{
	if (WindowsEngine* engine = GetEngine())
	{
		return engine->CommandAllocator;
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

RenderingResourcesUpdate::RenderingResourcesUpdate()
{

}

RenderingResourcesUpdate::~RenderingResourcesUpdate()
{
	if (UploadBuffer != nullptr)
	{
		UploadBuffer->Unmap(0, NULL);
		UploadBuffer = nullptr;
	}
}

void RenderingResourcesUpdate::Init(ID3D12Device* InDevice, UINT InElemetSize, UINT InElemetCount)
{
	assert(InDevice);

	ElementSize = InElemetSize;
	CD3DX12_HEAP_PROPERTIES HeapPropertie = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC ResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(InElemetSize * InElemetCount);
	ANALYSIS_HRESULT(InDevice->CreateCommittedResource(
		&HeapPropertie,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&UploadBuffer)));

	ANALYSIS_HRESULT(UploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&Data)));
}

void RenderingResourcesUpdate::Update(int Index, const void* InData)
{
	memcpy(&Data[Index * ElementSize], InData, ElementSize);
}

UINT RenderingResourcesUpdate::GetConstantBufferByteSize(UINT InTypeSzie)
{
	//222
	//256
	//454
	//512
	//(InTypeSzie + 255)& ~255;

	/*if (!(InTypeSzie % 256))
	{
		float NewFloat =  (float) InTypeSzie / 256.f;
		int Num = (NewFloat += 1);
		InTypeSzie = Num * 256;
	}*/

	//456
	//(456 + 255) & ~255;
	//711 & ~255;
	//0x02c7 & ~0x00ff
	//0x02c7 & 0xff00
	//0x0200
	return (InTypeSzie + 255) & ~255;
}

UINT RenderingResourcesUpdate::GetConstantBufferByteSize()
{
	return GetConstantBufferByteSize(ElementSize);
}
