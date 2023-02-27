#include "RegisterInspector.h"
#include"RObject/PropertyObject.h"
map<std::string, shared_ptr<ClassInspectorMapping>> RegisterInspector::ClassMappings;
map<std::string, shared_ptr<PropertyInspectorMapping>> RegisterInspector::PropertyMappings;

void RegisterInspector::RegisterRProperty(const std::string& InPropertyName, shared_ptr<PropertyInspectorMapping> InMapping)
{
	if (InMapping && !InPropertyName.empty())
	{
		PropertyMappings.insert(std::pair<string, shared_ptr<PropertyInspectorMapping>>(InPropertyName, InMapping));
	}
}
void RegisterInspector::RegisterRClass(const std::string& InClassName, shared_ptr<ClassInspectorMapping> InMapping)
{
	if (InMapping && !InClassName.empty())
	{
		ClassMappings.insert(std::pair<string, shared_ptr<ClassInspectorMapping>>(InClassName, InMapping));
	}
}

shared_ptr<ClassInspectorMapping> RegisterInspector::FindClass(const std::string& InClassName)
{
	auto iterator = ClassMappings.find(InClassName);
	if (iterator != ClassMappings.end())
	{
		return iterator->second;
	}

	return nullptr;
}

shared_ptr<PropertyInspectorMapping> RegisterInspector::FindProperty(const std::string& InPropertyName)
{
	auto iterator = PropertyMappings.find(InPropertyName);
	if (iterator != PropertyMappings.end())
	{
		return iterator->second;
	}

	return nullptr;
}

bool RegisterInspector::UpdateClassWidget(RMinimalObject* InObject)
{
	if (InObject)
	{
		for (auto& Tmp : InObject->GetNativeClass().InheritClassTypes)
		{
			//需要考虑继承关系 映射继承的内容
			if (shared_ptr<ClassInspectorMapping> ClassDetailsMapping = FindClass(Tmp))
			{
				ClassDetailsMapping->UpdateDetailsWidget(InObject);
			}
		}
	}

	return false;
}

bool RegisterInspector::UpdatePropertyWidget(RPropertyObject* InProperty)
{
	if (InProperty)
	{
		std::map<std::string, std::vector<RPropertyObject*>> Categorys;
		auto AddCategory = [&](RPropertyObject* InNewProperty, const std::string& InCategoryName)
		{
			auto CategorysIt = Categorys.find(InCategoryName);
			if (CategorysIt != Categorys.end())
			{
				CategorysIt->second.push_back(InNewProperty);
			}
			else
			{
				Categorys.insert({ InCategoryName,std::vector<RPropertyObject*>() });

				Categorys[InCategoryName].push_back(InNewProperty);
			}
		};

		while (InProperty)
		{
			auto MateValue = InProperty->GetNativeClass().Metas.find("Category");
			if (MateValue != InProperty->GetNativeClass().Metas.end())
			{
				AddCategory(InProperty, MateValue->second);
			}

			InProperty = dynamic_cast<RPropertyObject*>(InProperty->Nest);
		}

		ImGui::Separator();
		for (auto& Tmp : Categorys)
		{
			if (ImGui::CollapsingHeader(Tmp.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				for (auto& SubTmp : Tmp.second)
				{
					if (auto InDetailsProperty = FindProperty(SubTmp->GetType().c_str()))
					{
						if (InDetailsProperty->UpdateDetailsWidget(SubTmp))
						{
							if (RMinimalObject* InObject = dynamic_cast<RMinimalObject*>(SubTmp->GetOuter()))
							{
								InObject->UpdateEditorPropertyDetails(SubTmp);
							}
						}
					}
				}
			}
		}
		ImGui::Separator();

		return true;
	}

	return false;
}