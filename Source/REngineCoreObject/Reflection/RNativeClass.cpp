#include "RNativeClass.h"
#include "../RObject/FunctionObject.h"
#include "../RObject/PropertyObject.h"

RNativeClass::RNativeClass()
	:Outer(NULL)
{
}

void RNativeClass::AddProperty(
	const std::string& PropertyName,
	const std::string& InType,
	int InCount,
	int InElementSize,
	void* InData)
{
	CreateObjectParam Param;
	Param.Outer = Outer;
	RPropertyObject* Ptr = CreateObject<RPropertyObject>(Param, new RPropertyObject());

	Ptr->SetCountValue(InCount);
	Ptr->SetElementSize(InElementSize);
	Ptr->SetTypeValue(InType);
	Ptr->InitializeValue(InData);

	Ptr->Rename(PropertyName);

	if (!Property)
	{
		Property = Ptr;
	}
	else
	{
		RPropertyObject* StartPtr = Property;
		while (StartPtr)
		{
			if (!StartPtr->Nest)
			{
				StartPtr->Nest = Ptr;

				StartPtr = nullptr;
			}
			else
			{
				StartPtr = dynamic_cast<RPropertyObject*>(StartPtr->Nest);
			}
		}
	}
}
