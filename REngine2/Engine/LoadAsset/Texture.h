#pragma once
#include"../EngineMinimal.h"
#include"../Interface/DXDeviceInterface.h"
struct RTexture
{
	RTexture()
		:HeapIndex(0)
	{}
	ComPtr<ID3D12Resource> Resource;
	ComPtr<ID3D12Resource> UploadHeap;
	int HeapIndex = 0;

	string Name;//贴图名称
	string Filename;//路径
	D3D12_SRV_DIMENSION Dimension = D3D12_SRV_DIMENSION_TEXTURE2D;
};

class RTextureManage: public IDirectXDeviceInterface
{
public:
	RTextureManage();
public:
	RTexture* FindRenderingTexture(const std::string& key);
	void LoadTextureFormPath(const std::string& name, const std::string& path);

	void BuildTextureConstantBuffer(ID3D12DescriptorHeap* InHeap, int Offset);

	//创建可用的texture资源
	void CreateTexture();

	void CreateTexture(
		std::string fileName,
		_Out_ ComPtr<ID3D12Resource>& texture,
		_Out_ ComPtr<ID3D12Resource>& textureUploadHeap);

	UINT GetTextureSize() { return m_TextureMap.size(); }
private:
	unordered_map<std::string, RTexture*> m_TextureMap;
	int NowTextureIndex;
};