#pragma once
#include "MeshType.h"
#include"../../Core/RObject/RMinimalObject.h"
#include "../../Render/Render.h"
#include "../../Shader/Shader.h"
#include"../../Actor/ActorObject.h"
#include"../../Interface/DXDeviceInterface.h"

class RMaterial;
class RMeshComponent;
class BMesh : public GActorObject, public IRenderingInterface, public IDirectXDeviceInterface
{
	typedef GActorObject Super;

	RVARIABLE()
	RMeshComponent* MeshComponent;
public:
	BMesh();

	virtual void Init();

	virtual void PreDraw(float DeltaTime);
	virtual void Draw(float DeltaTime);
	virtual void PostDraw(float DeltaTime);

	virtual void SetMeshComponent(RMeshComponent* InMeshComponent) { MeshComponent = InMeshComponent; }

	virtual RMeshComponent* GetMeshComponent() { return MeshComponent; }

	UINT GetMaterialsNum();

	vector<RMaterial*>* GetMaterials();

public:
	virtual void SetPosition(const XMFLOAT3& InNewPosition);
	virtual void SetRotation(const fvector_3d& InRotation);
	virtual void SetScale(const fvector_3d& InNewScale);
};