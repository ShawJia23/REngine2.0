#pragma once
#include"RObject/RMinimalObject.h"
#include"MaterialType.h"
#include"../EngineMinimal.h"
class RMaterial :public RMinimalObject
{
public:
	RMaterial();
	void SetMaterialDisplayState(EMaterialDisplayStatue displayState);
	void SetBaseColor(const fvector_4d& baseColor);
	void SetBaseColor(const std::string& InAssetFilename);
	void SetFloatParam(int ParamIndex, float InValue);
	void SetMaterialType(EMaterialType materialType);
	void SetRoughness(float	 roughness);

	void SetBaseColorIndexKey(const std::string& value);
	void SetNormalIndexKey(const std::string& value);
	void SetSpecularIndexKey(const std::string& value);
	void SetMaterialTransform(const XMFLOAT4X4& value);
	void SetMaterialIndex(int index);
	void SetDirty(bool bNewDirty);
	void SetSpecular(const fvector_3d& InVector);

	FORCEINLINE fvector_4d GetBaseColor()const { return m_BaseColor; }
	FORCEINLINE fvector_3d GetSpecularColor()const { return m_SpecularColor; }
	FORCEINLINE EMaterialType GetMaterialType()const { return m_MaterialType; }
	FORCEINLINE float GetRoughness()const { return m_Roughness; }
	FORCEINLINE EMaterialDisplayStatue GetMaterialDisplayState()const { return m_MaterialState; }
	FORCEINLINE bool IsDirty() const { return m_Dirty; }

	FORCEINLINE XMFLOAT4X4& GetMaterialTransform() { return m_MaterialTransform; }
	FORCEINLINE std::string& GetBaseColorIndexKey() { return m_BaseColorIndexKey; }
	FORCEINLINE std::string& GetNormalIndexKey() { return m_NormalIndexKey; }
	FORCEINLINE std::string& GetSpecularIndexKey() { return m_SpecularIndexKey; }
	FORCEINLINE int GetMaterialIndex() { return m_MaterialIndex; }

private:
	bool m_Dirty;

	fvector_4d m_BaseColor;
	std::string BaseColorIndexKey;
	fvector_3d m_SpecularColor;
	EMaterialType m_MaterialType;
	EMaterialDisplayStatue m_MaterialState;
	float	 m_Roughness;

	std::string m_BaseColorIndexKey;
	std::string m_NormalIndexKey;
	std::string m_SpecularIndexKey;
	XMFLOAT4X4 m_MaterialTransform;
	int m_MaterialIndex;
private:
	float Param0;//自定义
	float Param1;//自定义
	float Param2;//自定义
};