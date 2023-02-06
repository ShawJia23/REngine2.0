#pragma once
#include "FieldObject.h"

class RPropertyObject;

class RENGINECOREOBJECT_API RFunctionObject :public RFieldObject
{
public:
	RPropertyObject* Property;
	vector<unsigned char> Script;
};