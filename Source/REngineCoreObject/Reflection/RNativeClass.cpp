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

void RNativeClass::AddClassType(const std::string& InType)
{
	InheritClassTypes.push_back(InType);
}

RPropertyObject* RNativeClass::FindProperty(const std::string& InPropertyString)
{
	RPropertyObject* StartPtr = Property;
	while (StartPtr)
	{
		if (StartPtr->GetName() == InPropertyString)
		{
			return StartPtr;
		}

		StartPtr = dynamic_cast<RPropertyObject*>(StartPtr->Nest);
	}

	return nullptr;
}

bool RNativeClass::IsExitFields(const std::string& InField)
{
	return FindFields(InField) != -1;
}

int RNativeClass::FindFields(const std::string& InField)
{
	for (int i = 0; i < Fields.size(); i++)
	{
		if (Fields[i] == InField)
		{
			return i;
		}
	}

	return -1;
}

std::string* RNativeClass::FindMetas(const std::string& InKey)
{
	auto It = Metas.find(InKey);
	if (It != Metas.end())
	{
		return &It->second;
	}

	return nullptr;
}

void RNativeClass::AddMetas(const std::string& InKeyString, const std::string& InValue)
{
	if (InKeyString.length() != 0 && InValue.length() != 0)
	{
		Metas.insert({ InKeyString, InValue });
	}
}

void RNativeClass::AddMetas(const string& InPropertyName, const string& InKeyString, const string& InValue)
{
	if (InKeyString.length() != 0 && InValue.length() != 0)
	{
		if (RPropertyObject* InPropertyPtr = FindProperty(InPropertyName))
		{
			InPropertyPtr->GetNativeClass().AddMetas(InKeyString, InValue);
		}
	}
}

void RNativeClass::AddFields(const string& InPropertyName, const string& InFields)
{
	if (InFields.length() != 0)
	{
		if (RPropertyObject* InPropertyPtr = FindProperty(InPropertyName))
		{
			InPropertyPtr->GetNativeClass().AddFields(InFields);
		}
	}
}

void RNativeClass::AddFields(const string& InFields)
{
	if (InFields.length() != 0)
	{
		Fields.push_back(InFields);
	}
}