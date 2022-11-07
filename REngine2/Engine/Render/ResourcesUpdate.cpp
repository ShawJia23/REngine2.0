#include "ResourcesUpdate.h"

ResourcesUpdate::ResourcesUpdate()
{

}

ResourcesUpdate::~ResourcesUpdate()
{
	if (m_UploadBuffer != nullptr)
	{
		m_UploadBuffer->Unmap(0, NULL);
		m_UploadBuffer = nullptr;
	}
}

void ResourcesUpdate::Init(ID3D12Device* device, UINT elementSize, UINT elemetCount, bool bConstBuffer)
{
	assert(device);

	if (bConstBuffer)
	{
		m_elementSize = GetConstantBufferByteSize(elementSize);
	}
	else
	{
		m_elementSize = elementSize;
	}

	CD3DX12_HEAP_PROPERTIES HeapPropertie = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC ResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_elementSize * elemetCount);
	ANALYSIS_HRESULT(device->CreateCommittedResource(
		&HeapPropertie,
		D3D12_HEAP_FLAG_NONE,
		&ResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&m_UploadBuffer)));

	ANALYSIS_HRESULT(m_UploadBuffer->Map(0, nullptr, reinterpret_cast<void**>(&m_data)));
}

void ResourcesUpdate::Update(int index, const void* data)
{
	memcpy(&m_data[index * m_elementSize], data, m_elementSize);
}

UINT ResourcesUpdate::GetConstantBufferByteSize(UINT typeSzie)
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
	return (typeSzie + 255) & ~255;
}

UINT ResourcesUpdate::GetConstantBufferByteSize()
{
	return GetConstantBufferByteSize(m_elementSize);
}
