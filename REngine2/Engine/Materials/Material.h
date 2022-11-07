#pragma once
#include"../Core/RObject/RMinimalObject.h"
#include"MaterialType.h"
class RMaterial :public RMinimalObject
{
public:
	RMaterial();
	void SetMaterialDisplayState(EMaterialDisplayStatue displayState);
	void SetBaseColor(const fvector_4d& baseColor);
	void SetMaterialType(EMaterialType materialType);
	void SetRoughness(float	 roughness);

	void SetBaseColorIndexKey(const std::string& value);
	void SetMaterialTransform(const XMFLOAT4X4& value);
	void SetMaterialIndex(int index);
	void SetDirty(bool bNewDirty);


	FORCEINLINE fvector_4d GetBaseColor()const { return m_BaseColor; }
	FORCEINLINE EMaterialType GetMaterialType()const { return m_MaterialType; }
	FORCEINLINE float GetRoughness()const { return m_Roughness; }
	FORCEINLINE EMaterialDisplayStatue GetMaterialDisplayState()const { return m_MaterialState; }
	FORCEINLINE bool IsDirty() const { return m_Dirty; }

	FORCEINLINE XMFLOAT4X4& GetMaterialTransform() { return m_MaterialTransform; }
	FORCEINLINE std::string& GetBaseColorIndexKey() { return m_BaseColorIndexKey; }
	FORCEINLINE int GetMaterialIndex() { return m_MaterialIndex; }

private:
	bool m_Dirty;

	fvector_4d m_BaseColor;

	EMaterialType m_MaterialType;
	EMaterialDisplayStatue m_MaterialState;
	float	 m_Roughness;

	std::string m_BaseColorIndexKey;
	XMFLOAT4X4 m_MaterialTransform;
	int m_MaterialIndex;
};