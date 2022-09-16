#include "Mesh.h"
#include"../../Config/RenderConfig.h"

const float PI = 3.1415926535f;

BMesh::BMesh()
    :m_vertexSizeInBytes(0)
    , m_vertexStrideInBytes(0)
    , m_indexSizeInBytes(0)
    , m_indexFormat(DXGI_FORMAT_R16_UINT)
    , m_indexSize(0)
    , m_worldMatrix(ObjectTransformation::IdentityMatrix4x4())
    , m_viewMatrix(ObjectTransformation::IdentityMatrix4x4())
    , m_projectMatrix(ObjectTransformation::IdentityMatrix4x4())
{
}

void BMesh::Init()
{
    float AspectRatio = (float)EngineRenderConfig::GetRenderConfig()->ScrrenWidth / (float)EngineRenderConfig::GetRenderConfig()->ScrrenHight;
    //(1,1,0) (-1,1,0) (-1,-1,0) (1,-1,0) (1,1,1) (-1,1,1) (-1,-1,1) (1,-1,1)
    //������Ұ��������͸��ͶӰ����
    XMMATRIX Project = XMMatrixPerspectiveFovLH(
        0.25f * PI, //�Ի���Ϊ��λ�����϶��µ��ӳ��ǡ�
        AspectRatio,//��ͼ�ռ� X:Y ���ݺ�ȡ�
        1.0f,//��������ƽ��ľ��롣��������㡣
        1000.f//��Զ����ƽ��ľ��롣��������㡣
    );

    XMStoreFloat4x4(&m_projectMatrix, Project);
}

void BMesh::BuildMesh(const MeshRenderingData* renderingData)
{
    //����CBVջ����
    D3D12_DESCRIPTOR_HEAP_DESC HeapDesc;
    HeapDesc.NumDescriptors = 1;
    HeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    HeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    HeapDesc.NodeMask = 0;
    GetD3dDevice()->CreateDescriptorHeap(&HeapDesc, IID_PPV_ARGS(&m_CBVHeap));

    //�����������Ĺ���
    //////////////////////////////
    m_objectConstants = make_shared<RenderingResourcesUpdate>();
    m_objectConstants->Init(GetD3dDevice().Get(), sizeof(ObjectTransformation), 1);
    D3D12_GPU_VIRTUAL_ADDRESS ObAddr = m_objectConstants.get()->GetBuffer()->GetGPUVirtualAddress();

    D3D12_CONSTANT_BUFFER_VIEW_DESC CBVDesc;
    CBVDesc.BufferLocation = ObAddr;
    CBVDesc.SizeInBytes = m_objectConstants->GetConstantBufferByteSize();

    GetD3dDevice()->CreateConstantBufferView(
        &CBVDesc,
        m_CBVHeap->GetCPUDescriptorHandleForHeapStart());

    //������ǩ��
    CD3DX12_ROOT_PARAMETER RootParam[1];

    //CBV������
    CD3DX12_DESCRIPTOR_RANGE DescriptorRangeCBV;
    DescriptorRangeCBV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

    RootParam[0].InitAsDescriptorTable(1, &DescriptorRangeCBV);

    CD3DX12_ROOT_SIGNATURE_DESC RootSignatureDesc(
        1,
        RootParam,
        0,
        nullptr,
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    //����
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

    //����
    GetD3dDevice()->CreateRootSignature(
        0,
        SerializeRootSignature->GetBufferPointer(),
        SerializeRootSignature->GetBufferSize(),
        IID_PPV_ARGS(&m_rootSignature));

    //Shader
    m_vertexShader.BuildShaders(L"../RenZhaiEngine/Shader/Hello.hlsl", "VertexShaderMain", "vs_5_0");
    m_pixelShader.BuildShaders(L"../RenZhaiEngine/Shader/Hello.hlsl", "PixelShaderMain", "ps_5_0");

    m_inputElementDesc =
    {
        {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
    };

    //����ģ��
    //////////////////////////
    m_vertexStrideInBytes = sizeof(RVertex);
    m_indexSize = renderingData->IndexData.size();

    //��ȡ��ģ�����ݵĴ�С
    m_vertexSizeInBytes = renderingData->VertexData.size() * m_vertexStrideInBytes;
    m_indexSizeInBytes = m_indexSize * sizeof(uint16_t);

    ANALYSIS_HRESULT(D3DCreateBlob(m_vertexSizeInBytes, &m_CPUVertexBufferPtr));
    memcpy(m_CPUVertexBufferPtr->GetBufferPointer(), renderingData->VertexData.data(), m_vertexSizeInBytes);

    ANALYSIS_HRESULT(D3DCreateBlob(m_indexSizeInBytes, &m_CPUIndexBufferPtr));
    memcpy(m_CPUIndexBufferPtr->GetBufferPointer(), renderingData->IndexData.data(), m_indexSizeInBytes);

    m_GPUVertexBufferPtr = ConstructDefaultBuffer(
        m_vertexBufferTmpPtr,
        renderingData->VertexData.data(), m_vertexSizeInBytes);

    m_GPUIndexBufferPtr = ConstructDefaultBuffer(m_indexBufferTmpPtr,
        renderingData->IndexData.data(), m_indexSizeInBytes);

    //PSO ��ˮ�߰�
    D3D12_GRAPHICS_PIPELINE_STATE_DESC GPSDesc;
    memset(&GPSDesc, 0, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

    //�����벼��
    GPSDesc.InputLayout.pInputElementDescs = m_inputElementDesc.data();
    GPSDesc.InputLayout.NumElements = (UINT)m_inputElementDesc.size();

    //�󶨸�ǩ��
    GPSDesc.pRootSignature = m_rootSignature.Get();

    //�󶨶�����ɫ������
    GPSDesc.VS.pShaderBytecode = reinterpret_cast<BYTE*>(m_vertexShader.GetBufferPointer());
    GPSDesc.VS.BytecodeLength = m_vertexShader.GetBufferSize();

    //��������ɫ��
    GPSDesc.PS.pShaderBytecode = m_pixelShader.GetBufferPointer();
    GPSDesc.PS.BytecodeLength = m_pixelShader.GetBufferSize();

    //���ù�դ��״̬
    GPSDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

    //0000..0000
    GPSDesc.SampleMask = UINT_MAX;

    GPSDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    GPSDesc.NumRenderTargets = 1;

    GPSDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    GPSDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

    GPSDesc.SampleDesc.Count = GetEngine()->GetDXGISampleCount();
    GPSDesc.SampleDesc.Quality = GetEngine()->GetDXGISampleQuality();

    GPSDesc.RTVFormats[0] = GetEngine()->GetBackBufferFormat();
    GPSDesc.DSVFormat = GetEngine()->GetDepthStencilFormat();

    ANALYSIS_HRESULT(GetD3dDevice()->CreateGraphicsPipelineState(&GPSDesc, IID_PPV_ARGS(&m_PSO)))
}

void BMesh::PostDraw(float DeltaTime)
{
    XMUINT3 MeshPos = XMUINT3(5.0f, 5.0f, 5.0f);

    XMVECTOR Pos = XMVectorSet(MeshPos.x, MeshPos.y, MeshPos.z, 1.0f);
    XMVECTOR ViewTarget = XMVectorZero();
    XMVECTOR ViewUp = XMVectorSet(0.f, 1.0f, 0.f, 0.f);

    XMMATRIX ViewLookAt = XMMatrixLookAtLH(Pos, ViewTarget, ViewUp);
    XMStoreFloat4x4(&m_viewMatrix, ViewLookAt);

    XMMATRIX ATRIXWorld = XMLoadFloat4x4(&m_worldMatrix);
    XMMATRIX ATRIXProject = XMLoadFloat4x4(&m_projectMatrix);
    XMMATRIX WVP = ATRIXWorld * ViewLookAt * ATRIXProject;

    ObjectTransformation objectTransformation;
    XMStoreFloat4x4(&objectTransformation.World, XMMatrixTranspose(WVP));
    m_objectConstants->Update(0, &objectTransformation);
}

void BMesh::Draw(float DeltaTime)
{
    ID3D12DescriptorHeap* DescriptorHeap[] = { m_CBVHeap.Get() };
    GetGraphicsCommandList()->SetDescriptorHeaps(_countof(DescriptorHeap), DescriptorHeap);

    GetGraphicsCommandList()->SetGraphicsRootSignature(m_rootSignature.Get());

    D3D12_VERTEX_BUFFER_VIEW VBV = GetVertexBufferView();

    //����Ⱦ��ˮ���ϵ�����ۣ�����������װ�����׶δ��붥������
    GetGraphicsCommandList()->IASetVertexBuffers(
        0,//��ʼ����� 0-15 
        1,//k k+1 ... k+n-1 
        &VBV);

    D3D12_INDEX_BUFFER_VIEW IBV = GetIndexBufferView();
    GetGraphicsCommandList()->IASetIndexBuffer(&IBV);

    //��������Ҫ���Ƶ�����ͼԪ �� �� ��
    GetGraphicsCommandList()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    GetGraphicsCommandList()->SetGraphicsRootDescriptorTable(0, m_CBVHeap->GetGPUDescriptorHandleForHeapStart());

    //�����Ļ���
    GetGraphicsCommandList()->DrawIndexedInstanced(
        m_indexSize,//��������
        1,//����ʵ������
        0,//���㻺������һ�������Ƶ�����
        0,//GPU ��������������ȡ�ĵ�һ��������λ�á�
        0);//�ڴӶ��㻺������ȡÿ��ʵ������֮ǰ��ӵ�ÿ��������ֵ��
}

void BMesh::PreDraw(float DeltaTime)
{
    GetGraphicsCommandList()->Reset(GetCommandAllocator().Get(), m_PSO.Get());
}

BMesh* BMesh::CreateMesh(const MeshRenderingData* renderingData)
{
    BMesh* InMesh = new BMesh();
    InMesh->BuildMesh(renderingData);
    return InMesh;
}

D3D12_VERTEX_BUFFER_VIEW BMesh::GetVertexBufferView()
{
    D3D12_VERTEX_BUFFER_VIEW VBV;
    VBV.BufferLocation = m_GPUVertexBufferPtr->GetGPUVirtualAddress();
    VBV.SizeInBytes = m_vertexSizeInBytes;
    VBV.StrideInBytes = m_vertexStrideInBytes;

    return VBV;
}

D3D12_INDEX_BUFFER_VIEW BMesh::GetIndexBufferView()
{
    D3D12_INDEX_BUFFER_VIEW IBV;
    IBV.BufferLocation = m_GPUIndexBufferPtr->GetGPUVirtualAddress();
    IBV.SizeInBytes = m_indexSizeInBytes;
    IBV.Format = m_indexFormat;

    return IBV;
}

ObjectTransformation::ObjectTransformation()
    :World(ObjectTransformation::IdentityMatrix4x4())
{
}

XMFLOAT4X4 ObjectTransformation::IdentityMatrix4x4()
{
    return XMFLOAT4X4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f);
}
