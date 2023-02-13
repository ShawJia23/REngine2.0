#include "RegisterInspector.h"

map<std::string, shared_ptr<PropertyInspectorMapping>> RegisterInspector::PropertyMappings;

void RegisterInspector::RegisterProperty(const std::string& InPropertyName, shared_ptr<PropertyInspectorMapping> InMapping)
{
	if (InMapping && !InPropertyName.empty())
	{
		PropertyMappings.insert(std::pair<string, shared_ptr<PropertyInspectorMapping>>(InPropertyName, InMapping));
	}
}