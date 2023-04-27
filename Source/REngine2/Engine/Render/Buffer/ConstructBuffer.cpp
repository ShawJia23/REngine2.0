#include "ConstructBuffer.h"
#include"../../Debug/EngineLog.h"
#include"../Engine/DXRenderEngine.h"
namespace ConstructBuffer
{
	ComPtr<ID3D12Resource> RConstructBuffer::ConstructDefaultBuffer(ComPtr<ID3D12Resource>& OutTmpBuffer, const void* InData, UINT64 InDataSize)
	{
		ComPtr<ID3D12Resource> Buffer;

		CD3DX12_RESOURCE_DESC BufferResourceDESC = CD3DX12_RESOURCE_DESC::Buffer(InDataSize);
		CD3DX12_HEAP_PROPERTIES BufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		ANALYSIS_HRESULT(DXRenderEngine::getInstance().GetD3dDevice()->CreateCommittedResource(
			&BufferProperties,
			D3D12_HEAP_FLAG_NONE,
			&BufferResourceDESC,
			D3D12_RESOURCE_STATE_COMMON,
			NULL, IID_PPV_ARGS(Buffer.GetAddressOf())));

		CD3DX12_HEAP_PROPERTIES UpdateBufferProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		ANALYSIS_HRESULT(DXRenderEngine::getInstance().GetD3dDevice()->CreateCommittedResource(
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

		DXRenderEngine::getInstance().GetCommandList()->ResourceBarrier(1, &CopyDestBarrier);

		//更新子资源，应该填充所有子资源数组
		UpdateSubresources<1>(
			DXRenderEngine::getInstance().GetCommandList().Get(),
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
}