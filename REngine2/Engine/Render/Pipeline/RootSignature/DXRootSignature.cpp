#include "DXRootSignature.h"

RDXRootSignature::RDXRootSignature()
{
}

void RDXRootSignature::BuildRootSignature(UINT textureNum)
{
    CD3DX12_ROOT_PARAMETER RootParam[5];

    CD3DX12_DESCRIPTOR_RANGE DescriptorRangeObjectCBV;
    DescriptorRangeObjectCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

    CD3DX12_DESCRIPTOR_RANGE DescriptorRangeViewportCBV;
    DescriptorRangeViewportCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

    CD3DX12_DESCRIPTOR_RANGE DescriptorRangeLightCBV;
    DescriptorRangeLightCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 2);

    CD3DX12_DESCRIPTOR_RANGE DescriptorRangeTextureSRV;
    DescriptorRangeTextureSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, textureNum, 3);

    RootParam[0].InitAsDescriptorTable(1, &DescriptorRangeObjectCBV);
    RootParam[1].InitAsDescriptorTable(1, &DescriptorRangeViewportCBV);
    RootParam[2].InitAsDescriptorTable(1, &DescriptorRangeLightCBV);
    RootParam[3].InitAsDescriptorTable(1, &DescriptorRangeTextureSRV);

    RootParam[4].InitAsShaderResourceView(4, 1);

    CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc(
        5,
        RootParam,
        0,
        nullptr,
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
