#pragma once
#include"../../../EngineMinimal.h"
struct RDXRootSignature
{
	RDXRootSignature();

	void BuildRootSignature(UINT textureNum);
	void SetRootSignature();
	ID3D12RootSignature* GetRootSignature() { return m_RootSignature.Get(); }
private:
	ComPtr<ID3D12RootSignature> m_RootSignature;
};