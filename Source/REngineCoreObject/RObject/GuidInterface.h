#pragma once
#include"../RCoreObjectMinimal.h"
#include"../RObjectMacro.h"
class RENGINECOREOBJECT_API IGuidInterface
{
public:
	IGuidInterface();

	bool operator==(const IGuidInterface& InOther)
	{
		return guid_equal(&m_guid, &InOther.m_guid);
	}

	string GetGuidString() const;
	simple_c_guid GetGuid() { return m_guid; }
private:
	simple_c_guid m_guid;
};