#pragma once
#include"../../../Interface/DXDeviceInterface.h"

struct RDXRootSignature :public IDirectXDeviceInterface_Struct
{
	RDXRootSignature();

	void BuildRootSignature();
	void SetRootSignature();
	ID3D12RootSignature* GetRootSignature() { return m_RootSignature.Get(); }
private:
	ComPtr<ID3D12RootSignature> m_RootSignature;
};