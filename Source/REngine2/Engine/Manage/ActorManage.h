#pragma once
#include"../EngineMinimal.h"
#include"../Core/public_singleton.h"


class RActorManage : public PublicSingleton<RActorManage>
{
public:
	RActorManage();
	~RActorManage();
	void LoadObject();
	void LoadAsset();
	void LoadModel(const char* inPath, const char* inName,
		const XMFLOAT3& newPosition, const fvector_3d& newScale);
};