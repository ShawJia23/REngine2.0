#include"BaseRenderLayer.h"
#include"../../../Core/ViewPort/ViewportInfo.h"
#include"../../../Component/RComponentMinimal.h"
#include"../BufferView/ConstantBufferView.h"
#include"../../ConstontBuffer/ObjectTransformation.h"
#include"../Geometry/RenderMeshData.h"

RenderLayer::RenderLayer():RenderLayerType(EMeshRenderLayerType::RENDERLAYER_OPAQUE)
{

}

void RenderLayer::SetPipelineState(RDXPipelineState* pipelineState)
{
	m_PipelineState = pipelineState;
}

void RenderLayer::DrawMesh(map<int, RGeometry> geometrys, ID3D12DescriptorHeap* heap, RConstantBufferView objectConstantBufferView)
{
	m_PipelineState->ResetPSO((int)RenderLayerType);

	UINT m_DescriptorOffset = GetD3dDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	UINT MeshOffset = objectConstantBufferView.GetConstantBufferByteSize();

	for (auto& Tmp : m_RenderDatas) 
	{
		D3D12_GPU_VIRTUAL_ADDRESS FirstVirtualMeshAddress = objectConstantBufferView.GetBuffer()->GetGPUVirtualAddress();

		D3D12_VERTEX_BUFFER_VIEW VBV = geometrys[Tmp.lock()->GeometryIndex].GetVertexBufferView();
		D3D12_INDEX_BUFFER_VIEW IBV = geometrys[Tmp.lock()->GeometryIndex].GetIndexBufferView();

		GetCommandList()->IASetIndexBuffer(&IBV);

		//����Ⱦ��ˮ���ϵ�����ۣ�����������װ�����׶δ��붥������
		GetCommandList()->IASetVertexBuffers(
			0,//��ʼ����� 0-15 
			1,//k k+1 ... k+n-1 
			&VBV);

		//��������Ҫ���Ƶ�����ͼԪ �� �� ��
		EMaterialDisplayStatue pDisplayState = (*Tmp.lock()->Mesh->GetMaterials())[0]->GetMaterialDisplayState();
		GetCommandList()->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)pDisplayState);

		D3D12_GPU_VIRTUAL_ADDRESS VAddress =
			FirstVirtualMeshAddress + Tmp.lock()->ObjectIndex * MeshOffset;

		GetCommandList()->SetGraphicsRootConstantBufferView(0, VAddress);

		GetCommandList()->DrawIndexedInstanced(
			Tmp.lock()->IndexSize,//��������
			1,//����ʵ������
			Tmp.lock()->IndexOffsetPosition,//���㻺������һ�������Ƶ�����
			Tmp.lock()->VertexOffsetPosition,//GPU ��������������ȡ�ĵ�һ��������λ�á�
			0);//�ڴӶ��㻺������ȡÿ��ʵ������֮ǰ��ӵ�ÿ��������ֵ��
	}

}

void RenderLayer::UpdateCalculations(const ViewportInfo viewportInfo, RConstantBufferView objectConstantBufferView)
{
	XMMATRIX ViewMatrix = XMLoadFloat4x4(&viewportInfo.ViewMatrix);
	XMMATRIX ProjectMatrix = XMLoadFloat4x4(&viewportInfo.ProjectMatrix);

	for (size_t i = 0; i < GetRenderDataSize(); i++)
	{
	    auto pRenderData = m_RenderDatas[i];
		
		//����ģ�͵�world
		{
			XMFLOAT3& Position = pRenderData.lock().get()->Mesh->GetPosition();
			fvector_3d Scale = pRenderData.lock().get()->Mesh->GetScale();

			XMFLOAT3 RightVector = pRenderData.lock().get()->Mesh->GetRightVector();
			XMFLOAT3 UPVector = pRenderData.lock().get()->Mesh->GetUPVector();
			XMFLOAT3 ForwardVector = pRenderData.lock().get()->Mesh->GetForwardVector();

			pRenderData.lock().get()->WorldMatrix = {
				RightVector.x * Scale.x,	UPVector.x,				ForwardVector.x ,			0.f,
				RightVector.y,				UPVector.y * Scale.y,	ForwardVector.y,			0.f,
				RightVector.z,				UPVector.z ,			ForwardVector.z * Scale.z,	0.f,
				Position.x,					Position.y,				Position.z,					1.f };
		}

		//����ģ��λ��
		XMMATRIX ATRIXWorld = XMLoadFloat4x4(&pRenderData.lock().get()->WorldMatrix);
		XMMATRIX ATRIXTextureTransform = XMLoadFloat4x4(&pRenderData.lock().get()->TextureTransform);

		RObjectTransformation ObjectTransformation;
		XMStoreFloat4x4(&ObjectTransformation.World, XMMatrixTranspose(ATRIXWorld));
		XMStoreFloat4x4(&ObjectTransformation.TextureTransformation, XMMatrixTranspose(ATRIXTextureTransform));
		//�ռ�����Index
		if (auto& InMater = (*pRenderData.lock().get()->Mesh->GetMaterials())[0])
		{
			ObjectTransformation.MaterialIndex = InMater->GetMaterialIndex();
		}

		objectConstantBufferView.Update(pRenderData.lock().get()->ObjectIndex, &ObjectTransformation);
	}
}

void RenderLayer::BuildPSO(UINT size)
{
	BuildShader(size);

	m_PipelineState->Build();
}

void RenderLayer::SetRenderLayerType(EMeshRenderLayerType type) 
{ 
	RenderLayerType = type; 
}
void RenderLayer::AddRenderData(std::shared_ptr<RRenderData> data)
{
	m_RenderDatas.push_back(data);
}

EMeshRenderLayerType RenderLayer::GetRenderLayerType() const 
{ 
	return RenderLayerType;
}
vector<std::weak_ptr<RRenderData>> RenderLayer::GetRenderDatas()
{ 
	return m_RenderDatas;
}
UINT RenderLayer::GetRenderDataSize()
{ 
	return m_RenderDatas.size();
}