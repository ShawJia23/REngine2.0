#pragma once
#include"RObject/RMinimalObject.h"
#include"../EngineMinimal.h"
#include"ActorObject.CodeReflection.h"
class RTransformComponent;

class GActorObject :public RMinimalObject
{
	CODEREFLECTION()

	RVARIABLE()
	RTransformComponent* TransformationComponent;

public:
	GActorObject();

public:
	FORCEINLINE RTransformComponent* GetTransformationComponent() const { return TransformationComponent; }
public:
	void SetPosition(const XMFLOAT3& InNewPosition);
	void SetRotation(const fvector_3d& InRotation);
	void SetScale(const fvector_3d& InNewScale);

public:
	XMFLOAT3& GetPosition();
	fvector_3d GetRotation()const;
	fvector_3d GetScale()const;

	XMFLOAT3& GetForwardVector();
	XMFLOAT3& GetRightVector();
	XMFLOAT3& GetUPVector();
public:
	RVARIABLE(CodeType = Resources)
	bool PlayerState;

	RVARIABLE(CodeType = Resources)
	int helloInt;

	RVARIABLE(CodeType = Resources)
	float helloFloat123;


	RVARIABLE(CodeType = Resources)
	string NameXXXX;

	RVARIABLE(CodeType = Resources)
	vector<int> TTTT;

	RVARIABLE(CodeType = Resources)
	map<int,string> TTTT1234567;

	RFUNCTION(CodeType = Event)
	static void Hello123(int c, float b);

	RFUNCTION(CodeType = Event)
	static void Hello();

	RFUNCTION(CodeType = Function)
	static void Hello1() {}

	RFUNCTION(CodeType = PureFunction)
	static void Hello2() {}
};