#include"PropertyInspectorMapping.h"
#include"RObject/PropertyObject.h"
void PropertyInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
}

/// <summary>
/// ////
/// </summary>
/// <param name="InProperty"></param>
void IntInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	ImGui::InputInt(InProperty->GetName().c_str(), InProperty->GetData<int>());
}

shared_ptr<PropertyInspectorMapping> IntInspectorMapping::MakeDetailsMapping()
{
	return make_shared<IntInspectorMapping>();
}


/// <summary>
/// /////
/// </summary>
/// <param name="InProperty"></param>
void FloatInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	ImGui::InputFloat(InProperty->GetName().c_str(), InProperty->GetData<float>());
}

shared_ptr<PropertyInspectorMapping> FloatInspectorMapping::MakeDetailsMapping()
{
	return make_shared<FloatInspectorMapping>();
}



/// <summary>
/// //////
/// </summary>
/// <param name="InProperty"></param>
void BoolInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	ImGui::Checkbox(InProperty->GetName().c_str(), InProperty->GetData<bool>());
}

shared_ptr<PropertyInspectorMapping> BoolInspectorMapping::MakeDetailsMapping()
{
	return make_shared<BoolInspectorMapping>();
}

/// <summary>
/// //////
/// </summary>
/// <param name="InProperty"></param>
void ArrayInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{

}

shared_ptr<PropertyInspectorMapping> ArrayInspectorMapping::MakeDetailsMapping()
{
	return make_shared<ArrayInspectorMapping>();
}


/// <summary>
/// ///////
/// </summary>
/// <param name="InProperty"></param>
void MapInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{

}

shared_ptr<PropertyInspectorMapping> MapInspectorMapping::MakeDetailsMapping()
{
	return make_shared<MapInspectorMapping>();
}


/// <summary>
/// ////////
/// </summary>
/// <param name="InProperty"></param>
void StringInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	char Buff[1024] = { 0 };
	string* BuffChar = InProperty->GetData<string>();
	strcpy(Buff, BuffChar->c_str());

	ImGui::InputText(
		InProperty->GetName().c_str(),
		Buff, 1024, ImGuiInputTextFlags_CallbackEdit,
		StringInspectorMapping::StringCallback,
		(void*)BuffChar);
}

int StringInspectorMapping::StringCallback(ImGuiInputTextCallbackData* InData)
{
	InData->Buf;
	string* UserDataString = (string*)InData->UserData;

	*UserDataString = InData->Buf;

	return 0;
}

shared_ptr<PropertyInspectorMapping> StringInspectorMapping::MakeDetailsMapping()
{
	return make_shared<StringInspectorMapping>();
}


/// <summary>
/// //////
/// </summary>
/// <param name="InProperty"></param>
void Vector3DInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	ImGui::InputFloat3(
		InProperty->GetName().c_str(),
		(float*)InProperty->GetData<fvector_3d>());
}

shared_ptr<PropertyInspectorMapping> Vector3DInspectorMapping::MakeDetailsMapping()
{
	return make_shared<Vector3DInspectorMapping>();
}