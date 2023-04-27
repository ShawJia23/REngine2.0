#include "EngineMinimal.h"
#include "Debug/Log/SimpleLog.h"
#include"Engine.h"
#include"Platform/Windows/WindowsEngine.h"
int Init(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
#if defined(_WIN32)
	WinMainCommandParameters WinMainParameters(hInstance, prevInstance, cmdLine, showCmd);
#endif 

	int ReturnValue = RWindowsEngine::getInstance().PreInit(
#if defined(_WIN32)
		WinMainParameters
#endif 
	);

	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine pre initialization error, check and initialization problem.", ReturnValue);
		return ReturnValue;
	}

	ReturnValue = RWindowsEngine::getInstance().Init(
#if defined(_WIN32)
		WinMainParameters
#endif 
	);
	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine initialization error, please check the initialization problem.", ReturnValue);
		return ReturnValue;
	}

	ReturnValue = RWindowsEngine::getInstance().PostInit();
	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine post initialization error, please check the initialization problem.", ReturnValue);
		return ReturnValue;
	}

	return ReturnValue;
}

void Tick()
{
	RWindowsEngine::getInstance().Tick();
}

int Exit()
{
	int ReturnValue = RWindowsEngine::getInstance().PreExit();
	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine pre exit failed.", ReturnValue);
		return ReturnValue;
	}

	ReturnValue = RWindowsEngine::getInstance().Exit();
	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine exit failed.", ReturnValue);
		return ReturnValue;
	}

	ReturnValue = RWindowsEngine::getInstance().PostExit();
	if (ReturnValue != 0)
	{
		Engine_Log_Error("[%i]Engine post exit failed.", ReturnValue);
		return ReturnValue;
	}

	return ReturnValue;
}

//hInstance 自己的实例
//prevInstance 上次的实例
//cmdLine 传递命令
//showCmd 多少条cmd
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	int ReturnValue = 0;

	//初始化
	Init(hInstance, prevInstance, cmdLine, showCmd);

	MSG EngineMsg = { 0 };

	//渲染出图
	while (EngineMsg.message != WM_QUIT)
	{
		//PM_NOREMOVE 消息不从队列里除掉。
		//PM_REMOVE   消息从队列里除掉。
		//PM_NOYIELD  此标志使系统不释放等待调用程序空闲的线程
		// 
		//PM_QS_INPUT 处理鼠标和键盘消息。
		//PM_QS_PAINT 处理画图消息。
		//PM_QS_POSTMESSAGE 处理所有被寄送的消息，包括计时器和热键。
		//PM_QS_SENDMESSAGE 处理所有发送消息。
		if (PeekMessage(&EngineMsg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&EngineMsg);
			DispatchMessage(&EngineMsg);
		}
		else
		{
			Tick();
		}

		//退出
		ReturnValue = Exit();
	}
	Engine_Log("[%i]The engine has exited.", ReturnValue);
	return ReturnValue;
}