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
	//显示新的手柄
	void SetNewSelectedOperationHandle(GActorObject* InNewSelectedObject);
	//设置选择对象
	void SetNewSelectedObject(GActorObject* InNewSelectedObject);

public:
	GActorObject* GetSelectedOperationHandle();
private:
	static OperationHandleManage* InManage;

	//记录当前的操作手柄 方便下次再显示出来
	GActorObject* SelectedOperationHandle;
};

#endif