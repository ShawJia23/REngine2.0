#include"Material.h"

RMaterial::RMaterial()
	:m_BaseColor(0.5f, 0.5f, 0.5f, 1.f),
	m_MaterialType(EMaterialType::Lambert),
	m_MaterialState(EMaterialDisplayStatue::RTOPOLOGY_TRIANGLELIST),
	m_Roughness(0)
{
}

void RMaterial::SetMaterialDisplayState(EMaterialDisplayStatue displayState)
{
	m_MaterialState = displayState;
}
