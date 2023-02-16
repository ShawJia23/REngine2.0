#pragma once
#include "PropertyInspectorMapping.h"
#include"ClassInspectorMapping.h"
class RegisterInspector
{
	friend class FDetailsEditor;

public:
	static void RegisterRClass(const std::string& InClassName, shared_ptr<ClassInspectorMapping> InMapping);
	static void RegisterRProperty(const std::string& InPropertyName, shared_ptr<PropertyInspectorMapping> InMapping);

	static shared_ptr<ClassInspectorMapping> FindClass(const std::string& InClassName);
	static shared_ptr<PropertyInspectorMapping> FindProperty(const std::string& InPropertyName);

	static bool UpdateClassWidget(RMinimalObject* InObject);
	static bool UpdatePropertyWidget(RPropertyObject* InProperty);

public:
	static map<std::string, shared_ptr<ClassInspectorMapping>> ClassMappings;
	static map<std::string, shared_ptr<PropertyInspectorMapping>> PropertyMappings;
};