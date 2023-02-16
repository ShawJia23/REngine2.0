#include "GuidInterface.h"

IGuidInterface::IGuidInterface()
{
	create_guid(&m_guid);
}

string IGuidInterface::GetGuidString() const
{
	char Buff[128] = { 0 };
	guid_to_string(Buff, &m_guid);

	return Buff;
}