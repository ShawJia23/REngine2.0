#pragma once
#include"../../Core/RObject/RMinimalObject.h"
#include"MaterialType.h"
class RMaterial :public RMinimalObject
{
public:
	RMaterial();
	void SetMaterialDisplayState(EMaterialDisplayStatue displayState);
	void SetBaseColor(const fvector_4d& baseColor) { m_BaseColor = baseColor; }
	void SetMaterialType(EMaterialType materialType) { m_MaterialType = materialType; }
	void SetRoughness(float	 roughness) { m_Roughness = roughness; }

	FORCEINLINE fvector_4d GetBaseColor()const { return m_BaseColor; }
	FORCEINLINE EMaterialType GetMaterialType()const { return m_MaterialType; }
	FORCEINLINE float GetRoughness()const { return m_Roughness; }
	FORCEINLINE EMaterialDisplayStatue GetMaterialDisplayState()const { return m_MaterialState; }
private:
	fvector_4d m_BaseColor;
	EMaterialType m_MaterialType;
	EMaterialDisplayStatue m_MaterialState;
	float	 m_Roughness;
};