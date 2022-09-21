#pragma once

#include"Viewport.h"
#include"RObject/RMinimalObject.h"

struct RInputKey;
class RTransformComponent;
class RInputComponent;

class RCamera :public RMinimalObject, public RViewport 
{
	RVARIABLE()
	RTransformComponent* m_rTransformComponent;

	RVARIABLE()
	RInputComponent* m_rInputComponent;

	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void ExecuteKeyboard(const RInputKey& inputKey);
public:
	RCamera();

	FORCEINLINE RTransformComponent* GetTransformComponent() { return m_rTransformComponent; }
	FORCEINLINE RInputComponent* GetInputComponent() { return m_rInputComponent; }
};