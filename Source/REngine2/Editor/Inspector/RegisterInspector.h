#pragma once
#include "PropertyInspectorMapping.h"

class RegisterInspector
{
	friend class FDetailsEditor;

public:
	static void RegisterProperty(const std::string& InPropertyName, shared_ptr<PropertyInspectorMapping> InMapping);

public:
	static map<std::string, shared_ptr<PropertyInspectorMapping>> PropertyMappings;
};