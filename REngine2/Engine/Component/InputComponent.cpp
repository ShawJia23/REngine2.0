#include"InputComponent.h"
void RInputComponent::Init()
{
}

void RInputComponent::Tick(float DeltaTime)
{
	if (m_captureKeyDelegate.IsBound()) 
	{
		RInputKey inputKey;
		m_captureKeyDelegate.Execute(inputKey);
	}
}
