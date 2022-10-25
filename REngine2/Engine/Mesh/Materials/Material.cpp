#include"Material.h"

RMaterial::RMaterial()
	:m_BaseColor(0.5f, 0.5f, 0.5f, 1.f),
	m_MaterialType(EMaterialType::Lambert)
{
}