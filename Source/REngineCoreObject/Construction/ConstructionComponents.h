#pragma once
#include"../RObjectMacro.h"

class RMinimalObject;
class RComponent;
struct CreateObjectParam;

namespace ConstructionComponent
{
	void RENGINECOREOBJECT_API UpdateConstructionComponents(RComponent* InComponent, RComponent* InParentComponent);
	void RENGINECOREOBJECT_API ConstructionComponents(const CreateObjectParam& InObjectParam, RMinimalObject* NewObject);
}