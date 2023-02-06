#pragma once
#include "RMinimalObject.h"

//提供核心对象
class RENGINECOREOBJECT_API RFieldObject :public RMinimalObject
{
	typedef RMinimalObject Super;

public:
	RFieldObject();

	RFieldObject* Nest;
};