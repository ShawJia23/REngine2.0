#pragma once
#include"../EngineMinimal.h"
#include"../Core/public_singleton.h"
struct RTexture
{
	RTexture()
		:HeapIndex(0)
	{}
	ComPtr<ID3D12Resource> Resource;
	ComPtr<ID3D12Resource> UploadHeap;
	int HeapIndex = 0;

	string Name;//��ͼ����
	string Filename;//·��
	D3D12_SRV_DIMENSION Dimension = D3D12_SRV_DIMENSION_TEXTURE2D;
};

class RTextureManage:public PublicSingleton<RTextureManage>
{
public:
	RTextureManage();
public:
	RTexture* FindRenderingTexture(const std::string& key);
	int  FindRenderingTextureIndex(const std::string& key);
	void LoadTextureFormPath(const std::string& name, const std::string& path);

	void BuildTextureConstantBuffer(ID3D12DescriptorHeap* InHeap, int Offset);

	//�������õ�texture��Դ
	void CreateTexture();

	void CreateTexture(
		std::string fileName,
		_Out_ ComPtr<ID3D12Resource>& texture,
		_Out_ ComPtr<ID3D12Resource>& textureUploadHeap);

	UINT GetTextureSize();

	void LoadCubeMapFormPath(const std::string& name, const std::string& path);
private:
	unordered_map<std::string, RTexture*> m_TextureMap;
	RTexture* m_CubeMap;
	int NowTextureIndex;
};