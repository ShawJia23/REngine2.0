#pragma once
#include "RMinimalObject.h"

//�ṩ���Ķ���
class RENGINECOREOBJECT_API RFieldObject :public RMinimalObject
{
	typedef RMinimalObject Super;

public:
	RFieldObject();

	RFieldObject* Nest;
};