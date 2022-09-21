#pragma once
#include "../../EngineMinimal.h"

class IGuidInterface
{
public:
	IGuidInterface();

	bool operator==(const IGuidInterface& InOther)
	{
		return guid_equal(&m_guid, &InOther.m_guid);
	}

	simple_c_guid GetGuid() { return m_guid; }
private:
	simple_c_guid m_guid;
};