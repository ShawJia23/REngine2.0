#pragma once

#include"RComponent/RComponent.h"
#include"../EngineMinimal.h"
#include"Input/RInputType.h"

DEFINITION_SIMPLE_SINGLE_DELEGATE(RCaptureKeyBoardDelegate, void, const RInputKey &);

class RInputComponent:public RComponent
{
public:
	RVARIABLE()
	RCaptureKeyBoardDelegate m_captureKeyDelegate;

	virtual void Init();
	virtual void Tick(float DeltaTime);
};

