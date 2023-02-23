#include "DXRootSignature.h"


std::vector<CD3DX12_STATIC_SAMPLER_DESC> GetStaticSamplers()
{
	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return { pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp };
}

RDXRootSignature::RDXRootSignature()
{
}

void RDXRootSignature::BuildRootSignature(UINT textureNum)
{
    CD3DX12_ROOT_PARAMETER RootParam[6];
	CD3DX12_DESCRIPTOR_RANGE DescriptorRangeTextureSRV;
	DescriptorRangeTextureSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, textureNum, 1);

	CD3DX12_DESCRIPTOR_RANGE DescriptorRangeCubeMapSRV;
	DescriptorRangeCubeMapSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

    RootParam[0].InitAsConstantBufferView(0);
    RootParam[1].InitAsConstantBufferView(1);
    RootParam[2].InitAsConstantBufferView(2);

    RootParam[3].InitAsShaderResourceView(0, 1);

	RootParam[4].InitAsDescriptorTable(1, &DescriptorRangeTextureSRV, D3D12_SHADER_VISIBILITY_PIXEL);
	RootParam[5].InitAsDescriptorTable(1, &DescriptorRangeCubeMapSRV, D3D12_SHADER_VISIBILITY_PIXEL);

	auto staticSamplers = GetStaticSamplers();
    CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc(
        6,
        RootParam,
		(UINT)staticSamplers.size(),
		staticSamplers.data(),
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    ComPtr<ID3DBlob> SerializeRootSignature;
    ComPtr<ID3DBlob> ErrorBlob;
    D3D12SerializeRootSignature(
        &RootSignatureDesc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        SerializeRootSignature.GetAddressOf(),
        ErrorBlob.GetAddressOf());

    if (ErrorBlob)
    {
        Engine_Log_Error("%s", (char*)ErrorBlob->GetBufferPointer());
    }

    GetD3dDevice()->CreateRootSignature(
        0,
        SerializeRootSignature->GetBufferPointer(),
        SerializeRootSignature->GetBufferSize(),
        IID_PPV_ARGS(&m_RootSignature));
}

void RDXRootSignature::SetRootSignature()
{
    GetCommandList()->SetGraphicsRootSignature(m_RootSignature.Get());
}
