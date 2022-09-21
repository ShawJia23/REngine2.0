#include "GuidInterface.h"

IGuidInterface::IGuidInterface()
{
	create_guid(&m_guid);
}