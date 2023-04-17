#pragma once
#include"../EngineMinimal.h"
#include"../Interface/DXDeviceInterface.h"


class RActorManage : public IDirectXDeviceInterface
{
public:
	RActorManage();
	~RActorManage();
	void LoadObject();
	void LoadAsset();
	void LoadModel(const char* inPath, const char* inName,
		const XMFLOAT3& newPosition, const fvector_3d& newScale);
public:
	RLightManage* m_lightManage;
	RTextureManage* m_textureManage;
};