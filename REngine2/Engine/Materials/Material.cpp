#include"Material.h"

RMaterial::RMaterial()
	:m_BaseColor(0.5f, 0.5f, 0.5f, 1.f),
	m_MaterialType(EMaterialType::Lambert),
	m_MaterialState(EMaterialDisplayStatue::RTOPOLOGY_TRIANGLELIST),
	m_Roughness(0),
	m_MaterialIndex(-1),
	m_MaterialTransform(RMath::IdentityMatrix4x4())
{
}

void RMaterial::SetMaterialDisplayState(EMaterialDisplayStatue displayState)
{
	m_MaterialState = displayState;
	SetDirty(true);
}

void RMaterial::SetBaseColor(const fvector_4d& baseColor) 
{ 
	m_BaseColor = baseColor;
	SetDirty(true);
}
void RMaterial::SetMaterialType(EMaterialType materialType) 
{ 
	m_MaterialType = materialType; 
	SetDirty(true);
}
void RMaterial::SetRoughness(float roughness)
{ 
	m_Roughness = roughness;
	SetDirty(true);
}

void RMaterial::SetBaseColorIndexKey(const std::string& value) 
{ 
	m_BaseColorIndexKey = value;
	SetDirty(true);
}
void RMaterial::SetMaterialTransform(const XMFLOAT4X4& value)
{ 
	m_MaterialTransform = value;
	SetDirty(true);
}
void RMaterial::SetMaterialIndex(int index) 
{
	m_MaterialIndex = index;
	SetDirty(true);
}
void RMaterial::SetDirty(bool bNewDirty) 
{
	m_Dirty = bNewDirty;
}