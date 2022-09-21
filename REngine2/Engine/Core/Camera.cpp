#include"Camera.h"
#include"../Component/TransformComponent.h"
#include"../Component/InputComponent.h"
RCamera::RCamera()
{
	m_rInputComponent = CreateObject<RInputComponent>(new RInputComponent());
	m_rTransformComponent = CreateObject<RTransformComponent>(new RTransformComponent());
}

void RCamera::Init()
{
	m_rInputComponent->m_captureKeyDelegate.Bind(this, &RCamera::ExecuteKeyboard);
}

void RCamera::Tick(float DeltaTime)
{
}

void RCamera::ExecuteKeyboard(const RInputKey& inputKey)
{

}