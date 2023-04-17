#include"ActorManage.h"
#include"../World.h"
#include"../Mesh/MeshMinimal.h"
#include"../Light/RLightMinimal.h"
#include"../Materials/Material.h"
#include"../Manage/TextureManage.h"
#include "Path/PathHelper.h"
#include "ImportSDK.h"
#include"../Manage/LightManage.h"
#include"../Component/RComponentMinimal.h"

#if EDITOR_ENGINE
#include"../../Editor/OperationHandle/MoveArrow.h"
#include"../../Editor/OperationHandle/RotatorArrow.h"
#include"../../Editor/OperationHandle/ScalingArrow.h"

extern RMoveArrow* MoveArrow;
//extern RScalingArrow* ScalingArrow;
//extern RRotatorArrow* RotatorArrow;
#endif

RActorManage::RActorManage() 
{
	m_lightManage = new RLightManage();
	m_textureManage = new RTextureManage();
}

RActorManage::~RActorManage()
{
	delete m_lightManage;
	delete m_textureManage;
}


void RActorManage::LoadObject() 
{
	////点光源
//if (GPointLight* pPointLight = m_World->CreateActorObject<GPointLight>())
//{
//	pPointLight->SetPosition(XMFLOAT3(0.f, 3.f, 4.f));
//	pPointLight->SetRotation(fvector_3d(0.f, 0.f, 0.f));

//	pPointLight->SetLightIntensity(fvector_3d(10.f, 10.f, 10.f));
//	pPointLight->SetEndAttenuation(150.f);
//}


//GPointLight* pLight = m_World->CreateActorObject<GPointLight>();
//if (pLight)
//{
//	pLight->SetPosition(XMFLOAT3(0.f, -10.f, 0.f));
//	pLight->SetRotation(fvector_3d(0.f, 0.f, 0.f));
//	pLight->SetLightIntensity(fvector_3d(10.f, 10.f, 10.f));
//	pLight->SetEndAttenuation(150.f);
//}

//构建Mesh
// 
//PlaneMesh* pMesh = m_World->CreateActorObject<PlaneMesh>();
//if (pMesh)
//{
//	pMesh->CreateMesh(4.f, 3.f, 20, 20);
//	pMesh->SetPosition(XMFLOAT3(0.f, -2.f, 0.f));
//	pMesh->SetScale(fvector_3d(20.f, 20.f, 10.f));
//	pMesh->SetPickup(false);
//}
	auto pLight = GetWorld()->CreateActorObject<GParallelLight>();
	if (pLight)
	{
		pLight->SetPosition(XMFLOAT3(0.f, 3.f, 4.f));
		pLight->SetRotation(fvector_3d(0, 0, 0));
	}

	auto pSMesh = GetWorld()->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10, EMeshRenderLayerType::RENDERLAYER_CUBEMAP);
		pSMesh->SetPosition(XMFLOAT3(0.f, 0.f, 0.f));
		pSMesh->SetScale(fvector_3d(200.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.2f, 0.2f, 0.2f, 1.f));
			pMaterial->SetSpecular(fvector_3d(0.2f));
			pMaterial->SetMaterialType(EMaterialType::BaseColor);
		}
		pSMesh->SetPickup(false);
	}


	/*SphereMesh* pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(8.f, 2, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::BlinnPhong);

			pMaterial->SetRoughness(0.8f);
		}
	}
	SphereMesh* pSMesh1 = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh1)
	{
		pSMesh1->CreateMesh(2.f, 10, 10);
		pSMesh1->SetPosition(XMFLOAT3(0.f, 6, 0.f));
		if (RMaterial* pMaterial = (*pSMesh1->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::WrapLight);
		}
	}

	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(-4.f, 6, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::Minnaert);
		}
	}
	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(8.f, 6, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::Banded);
		}
	}
	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(8.f, 10, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::GradualBanded);
		}
	}
	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(4.f, 10, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.5f, 0.5f, 0.5f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::FinalBanded);
			pMaterial->SetRoughness(0.8f);
		}
	}
	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(0.f, 10, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(0.2f, 0.8f, 0.3f, 1.f));
			pMaterial->SetMaterialType(EMaterialType::Back);
		}
	}

	pSMesh = m_World->CreateActorObject<SphereMesh>();
	if (pSMesh)
	{
		pSMesh->CreateMesh(2.f, 10, 10);
		pSMesh->SetPosition(XMFLOAT3(-4.f, 10, 0.f));
		if (RMaterial* pMaterial = (*pSMesh->GetMaterials())[0])
		{
			pMaterial->SetBaseColor(fvector_4d(1.f));
			pMaterial->SetMaterialType(EMaterialType::Normal);
		}
	}*/



}



void RActorManage::LoadAsset()
{
	if (RMoveArrow* InMoveArrow = GetWorld()->CreateActorObject<RMoveArrow>())
	{
		InMoveArrow->CreateMesh();

		MoveArrow = InMoveArrow;
	}

	//if (RScalingArrow* InScalingArrow = m_World->CreateActorObject<RScalingArrow>())
	//{
	//	InScalingArrow->CreateMesh();

	//	ScalingArrow = InScalingArrow;
	//}

	//if (RRotatorArrow* InRotatorArrow = m_World->CreateActorObject<RRotatorArrow>())
	//{
	//	InRotatorArrow->CreateMesh();

	//	RotatorArrow = InRotatorArrow;
	//}

	string AssetPath = PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineAssetPath());

	LoadModel((AssetPath + "/Model/yamato/yamato.obj").c_str(), "yamato",
		XMFLOAT3(0.f, 0.f, 0.f), fvector_3d(0.1f, 0.1f, 0.1f));

	LoadModel((AssetPath + "/Model/shennvpiguan/shennvpiguan.pmx").c_str(), "shennvpiguan",
		XMFLOAT3(0.f, 0.f, 0.f), fvector_3d(0.5f, 0.5f, 0.5f));

	GetTextureManage()->CreateTexture();
	GetTextureManage()->LoadCubeMapFormPath("cubemap", AssetPath + "/Cubemap/grasscube1024.dds");
}

void RActorManage::LoadModel(const char* inPath, const char* inName,
	const XMFLOAT3& newPosition, const fvector_3d& newScale)
{
	RAssimpObj RenderData;
	RAssimpObject().LoadMeshData(inPath, inName, RenderData);

	int num = 0;
	for (auto& TmpModel : RenderData.ModelData)
	{
		num++;
		for (auto& MeshTmp : TmpModel.MeshData)
		{
			MeshRenderData pData;
			for (auto& VertexTmp : MeshTmp.VertexData)
			{
				pData.VertexData.push_back(RVertex());
				auto &pTempData = pData.VertexData.back();
				pTempData.Normal.x = VertexTmp.Normal.X;
				pTempData.Normal.y = VertexTmp.Normal.Y;
				pTempData.Normal.z = VertexTmp.Normal.Z;

				pTempData.Position.x = VertexTmp.Position.X;
				pTempData.Position.y = VertexTmp.Position.Y;
				pTempData.Position.z = VertexTmp.Position.Z;

				pTempData.TangentU.x = VertexTmp.TangentU.X;
				pTempData.TangentU.y = VertexTmp.TangentU.Y;
				pTempData.TangentU.z = VertexTmp.TangentU.Z;

				pTempData.TexC.x = VertexTmp.TexC.X;
				pTempData.TexC.y = VertexTmp.TexC.Y;
			}
			for (auto& IndexData : MeshTmp.IndexData)
			{
				pData.IndexData.push_back(IndexData);
			}
			auto pMesh = GetWorld()->CreateActorObject<CustomMesh>();
			if (pMesh)
			{
				pMesh->SetMeshRenderData(pData);
				string name = inName + std::to_string(num);
				pMesh->CreateMesh(name);
				pMesh->SetPosition(newPosition);
				pMesh->SetScale(newScale);
				if (TmpModel.MaterialMap[0].DiffuseMapFileName.size() > 1)
				{
					GetTextureManage()->LoadTextureFormPath(inName + TmpModel.MaterialMap[0].DiffuseMapFileName, TmpModel.MaterialMap[0].DiffuseMapFileName);
					if (RMaterial* pMaterial = (*pMesh->GetMeshComponent()->GetMaterials())[0])
					{
						pMaterial->SetBaseColorIndexKey(inName + TmpModel.MaterialMap[0].DiffuseMapFileName);
						pMaterial->SetRoughness(0.8f);
					}
				}
			}
		}

	}
}