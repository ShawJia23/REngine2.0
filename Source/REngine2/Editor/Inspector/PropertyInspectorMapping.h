#pragma once
#include"InspectorMapping.h"

class RPropertyObject;
class PropertyInspectorMapping :public RInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping() { return nullptr; }
};

//int
class IntInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

//float
class FloatInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

//bool
class BoolInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

//array
class ArrayInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);
public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

//map
class MapInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

//string
class StringInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

	static int StringCallback(ImGuiInputTextCallbackData* InData);
public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

class Vector3DInspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};

class XMFLOAT3InspectorMapping :public PropertyInspectorMapping
{
public:
	virtual bool UpdateDetailsWidget(RPropertyObject* InProperty);

public:
	static shared_ptr<PropertyInspectorMapping> MakeDetailsMapping();
};