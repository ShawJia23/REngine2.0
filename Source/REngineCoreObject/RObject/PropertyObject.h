#pragma once
#include "FieldObject.h"

class RENGINECOREOBJECT_API RPropertyObject :public RFieldObject
{
public:
	int GetSize() const { return 0; }

	FORCEINLINE void InitializeValue(void* Dest) const {}
};