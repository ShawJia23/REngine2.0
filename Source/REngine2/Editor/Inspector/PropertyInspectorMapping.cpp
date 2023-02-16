#include"PropertyInspectorMapping.h"
#include"RObject/PropertyObject.h"
bool PropertyInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return false;
}

/// <summary>
/// ////
/// </summary>
/// <param name="InProperty"></param>
bool IntInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return ImGui::InputInt(InProperty->GetName().c_str(), InProperty->GetData<int>());
}

shared_ptr<PropertyInspectorMapping> IntInspectorMapping::MakeDetailsMapping()
{
	return make_shared<IntInspectorMapping>();
}


/// <summary>
/// /////
/// </summary>
/// <param name="InProperty"></param>
bool FloatInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return ImGui::InputFloat(InProperty->GetName().c_str(), InProperty->GetData<float>());
}

shared_ptr<PropertyInspectorMapping> FloatInspectorMapping::MakeDetailsMapping()
{
	return make_shared<FloatInspectorMapping>();
}



/// <summary>
/// //////
/// </summary>
/// <param name="InProperty"></param>
bool BoolInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return ImGui::Checkbox(InProperty->GetName().c_str(), InProperty->GetData<bool>());
}

shared_ptr<PropertyInspectorMapping> BoolInspectorMapping::MakeDetailsMapping()
{
	return make_shared<BoolInspectorMapping>();
}

/// <summary>
/// //////
/// </summary>
/// <param name="InProperty"></param>
bool ArrayInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return false;
}

shared_ptr<PropertyInspectorMapping> ArrayInspectorMapping::MakeDetailsMapping()
{
	return make_shared<ArrayInspectorMapping>();
}


/// <summary>
/// ///////
/// </summary>
/// <param name="InProperty"></param>
bool MapInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return false;
}

shared_ptr<PropertyInspectorMapping> MapInspectorMapping::MakeDetailsMapping()
{
	return make_shared<MapInspectorMapping>();
}


/// <summary>
/// ////////
/// </summary>
/// <param name="InProperty"></param>
bool StringInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	char Buff[1024] = { 0 };
	string* BuffChar = InProperty->GetData<string>();
	strcpy(Buff, BuffChar->c_str());

	return ImGui::InputText(
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
bool Vector3DInspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return ImGui::InputFloat3(
		InProperty->GetName().c_str(),
		(float*)InProperty->GetData<fvector_3d>());
}

shared_ptr<PropertyInspectorMapping> Vector3DInspectorMapping::MakeDetailsMapping()
{
	return make_shared<Vector3DInspectorMapping>();
}

bool XMFLOAT3InspectorMapping::UpdateDetailsWidget(RPropertyObject* InProperty)
{
	return false;
	//return ConstructDetailsWidget::ConstructFloat3Widget<fvector_3d>(InProperty);
}

shared_ptr<PropertyInspectorMapping> XMFLOAT3InspectorMapping::MakeDetailsMapping()
{
	return make_shared<XMFLOAT3InspectorMapping>();
}