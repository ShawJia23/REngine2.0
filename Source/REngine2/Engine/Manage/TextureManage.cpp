#include"TextureManage.h"
#include"ThirdParty/stb/stb_image.h"
#include"../LoadAsset/DDSTextureLoader.h"
std::wstring String2Wstring(std::string str)
{
	std::wstring result;
	//获取缓冲区大小，并申请空间，缓冲区大小按字符计算  
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	TCHAR* buffer = new TCHAR[len + 1];
	//多字节编码转换成宽字节编码  
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';             //添加字符串结尾  
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

string wstring2string(wstring wstr)
{
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
	int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

RTextureManage::RTextureManage():NowTextureIndex(0)
{
	
}

int  RTextureManage::FindRenderingTextureIndex(const std::string& key)
{
	if (!key.empty())
	{
		if (m_TextureMap.find(key) != m_TextureMap.end())//key
		{
			return m_TextureMap[key]->HeapIndex;
		}
	}

	return -1;
}

RTexture* RTextureManage::FindRenderingTexture(const std::string& key)
{
	if (!key.empty())
	{
		if (m_TextureMap.find(key) != m_TextureMap.end())//key
		{
			return m_TextureMap[key];
		}
	}

	return nullptr;
}

void RTextureManage::BuildTextureConstantBuffer(ID3D12DescriptorHeap* InHeap, int Offset)
{
	UINT DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	CD3DX12_CPU_DESCRIPTOR_HANDLE Handle(InHeap->GetCPUDescriptorHandleForHeapStart());
	Handle.Offset(Offset, DescriptorOffset);

	for (auto& Tmp : m_TextureMap)
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc = {};
		ShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ShaderResourceViewDesc.ViewDimension = Tmp.second->Dimension;
		ShaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		ShaderResourceViewDesc.Texture2D.MipLevels = 1;
		ShaderResourceViewDesc.Texture2D.ResourceMinLODClamp = 0.f;

		ShaderResourceViewDesc.Format = Tmp.second->Resource->GetDesc().Format;
		ShaderResourceViewDesc.Texture2D.MipLevels = Tmp.second->Resource->GetDesc().MipLevels;

		Tmp.second->HeapIndex = NowTextureIndex;
		NowTextureIndex++;

		GetD3dDevice()->CreateShaderResourceView(
			Tmp.second->Resource.Get(),
			&ShaderResourceViewDesc, Handle);

		Handle.Offset(1, DescriptorOffset);
	}
	{
		D3D12_SHADER_RESOURCE_VIEW_DESC ShaderResourceViewDesc = {};
		ShaderResourceViewDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		ShaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ShaderResourceViewDesc.ViewDimension = m_CubeMap->Dimension;
		ShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
		ShaderResourceViewDesc.TextureCube.MipLevels = m_CubeMap->Resource->GetDesc().MipLevels;
		ShaderResourceViewDesc.TextureCube.ResourceMinLODClamp = 0.f;

		ShaderResourceViewDesc.Format = m_CubeMap->Resource->GetDesc().Format;

		m_CubeMap->HeapIndex = NowTextureIndex;
		NowTextureIndex++;

		GetD3dDevice()->CreateShaderResourceView(
			m_CubeMap->Resource.Get(),
			&ShaderResourceViewDesc, Handle);

		Handle.Offset(1, DescriptorOffset);
	}
}

void RTextureManage::LoadTextureFormPath(const std::string& name,const std::string& path)
{
	auto Tex = new RTexture();
	Tex->Dimension = (D3D12_SRV_DIMENSION)D3D12_SRV_DIMENSION_TEXTURE2D;
	Tex->Name = name;
	Tex->Filename = path;
	m_TextureMap.try_emplace(name, Tex);
}

void RTextureManage::CreateTexture()
{
	for (auto& Tmp : m_TextureMap)
	{
		CreateTexture(Tmp.second->Filename, Tmp.second->Resource, Tmp.second->UploadHeap);
	}
}

void RTextureManage::CreateTexture(
	std::string fileName,
	_Out_ ComPtr<ID3D12Resource>& texture,
	_Out_ ComPtr<ID3D12Resource>& textureUploadHeap)
{
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(fileName.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	const UINT TexturePixelSize = 4;//由于是 rgb_alpha 所以是4通道

	D3D12_RESOURCE_DESC textureDesc = {};
	//暂定为1
	textureDesc.MipLevels = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.Width = texWidth;
	textureDesc.Height = texHeight;
	textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	textureDesc.DepthOrArraySize = 1;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	
	auto defaultHeap = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
	//创建szFileName：实际用的纹理资源   
	GetD3dDevice()->CreateCommittedResource(
		&defaultHeap,
		D3D12_HEAP_FLAG_NONE,
		&textureDesc,
		D3D12_RESOURCE_STATE_COPY_DEST,
		nullptr,
		IID_PPV_ARGS(texture.GetAddressOf()));

	const UINT num2DSubresources = textureDesc.DepthOrArraySize * textureDesc.MipLevels;
	//尺寸：
	const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture.Get(), 0, num2DSubresources);

	auto defaultUpload = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	auto ResourcesBuffer = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
	// Create the GPU upload buffer.
	ANALYSIS_HRESULT(GetD3dDevice()->CreateCommittedResource(
		&defaultUpload,
		D3D12_HEAP_FLAG_NONE,
		&ResourcesBuffer,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(textureUploadHeap.GetAddressOf())));


	auto TmpBarrier = CD3DX12_RESOURCE_BARRIER::Transition(
		texture.Get(),
		D3D12_RESOURCE_STATE_COMMON, 
		D3D12_RESOURCE_STATE_COPY_DEST);
	//将数据复制给中间资源，然后从中间资源复制给实际的资源
	GetCommandList()->ResourceBarrier(1, &TmpBarrier);

	D3D12_SUBRESOURCE_DATA textureData = {};
	textureData.pData = pixels;
	textureData.RowPitch = texWidth * TexturePixelSize;
	textureData.SlicePitch = textureData.RowPitch * texHeight;
	UpdateSubresources(GetCommandList().Get(), texture.Get(), textureUploadHeap.Get(), 0, 0, num2DSubresources, &textureData);


	auto TmpBarrier2 = CD3DX12_RESOURCE_BARRIER::Transition(
		texture.Get(),
		D3D12_RESOURCE_STATE_COPY_DEST, 
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
	GetCommandList()->ResourceBarrier(1, &TmpBarrier2);
}

void RTextureManage::LoadCubeMapFormPath(const std::string& name, const std::string& path)
{
	auto Tex = new RTexture();
	Tex->Dimension = (D3D12_SRV_DIMENSION)D3D12_SRV_DIMENSION_TEXTURECUBE;
	Tex->Name = name;
	Tex->Filename = path;
	auto Tmp=String2Wstring(Tex->Filename);
	CreateDDSTextureFromFile12(GetD3dDevice().Get(),
		GetCommandList().Get(), Tmp.c_str(),
		Tex->Resource, Tex->UploadHeap);

	m_CubeMap = std::move(Tex);
}