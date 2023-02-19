#pragma once
#include"../../Engine/EngineMacro.h"
#if EDITOR_ENGINE
class GActorObject;

class OperationHandleManage
{
public:
	OperationHandleManage();

	static OperationHandleManage* Get();
	static void Destroy();

public:
	void AllOperationHandleHide();

public:
	void DisplaySelectedOperationHandle(GActorObject* InNewSelectedObject);
	void DisplaySelectedOperationHandle();
	void HideSelectedOperationHandle();

public:
	//��ʾ�µ��ֱ�
	void SetNewSelectedOperationHandle(GActorObject* InNewSelectedObject);
	//����ѡ�����
	void SetNewSelectedObject(GActorObject* InNewSelectedObject);

public:
	GActorObject* GetSelectedOperationHandle();
private:
	static OperationHandleManage* InManage;

	//��¼��ǰ�Ĳ����ֱ� �����´�����ʾ����
	GActorObject* SelectedOperationHandle;
};

#endif