#pragma once
#include "FieldObject.h"

class RENGINECOREOBJECT_API RPropertyObject :public RFieldObject
{
public:
	RPropertyObject();

	template<class T>
	FORCEINLINE T* GetData() const
	{
		return (T*)Data;
	}

public:
	FORCEINLINE int GetElementSize() const { return ElementSize; }
	FORCEINLINE int GetCount() const { return Count; }
	FORCEINLINE void* GetData() const { return Data; }
	FORCEINLINE const string& GetType() const { return Type; }

public:
	FORCEINLINE void InitializeValue(void* InDest) { Data = InDest; }
	FORCEINLINE void SetElementSize(int InSize) { ElementSize = InSize; }
	FORCEINLINE void SetCountValue(int InCount) { Count = InCount; }
	FORCEINLINE void SetTypeValue(const string& InType) { Type = InType; }

private:
	void* Data;
	int Count;
	int ElementSize;
	string Type;
};