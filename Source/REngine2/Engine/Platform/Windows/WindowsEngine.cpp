#include "WindowsEngine.h"
#include"RObject/RMinimalObject.h"
#include "../../Debug/EngineLog.h"
#include "../../Config/RenderConfig.h"
#include "../../Render/Render.h"
#include"../../World.h"
#include"../../Render/Engine/DXRenderEngine.h"
#include"../../Camera/Camera.h"
#include"../../Manage/MeshManage.h"
#include"../../Manage/LightManage.h"
#include"../../Construction/MacroConstruction.h"
#include"../../Component/Input/Input.h"
#include "Path/PathHelper.h"
#include"../../../Timer/GameTimer.h"
#if EDITOR_ENGINE
#include"../../../Editor/Editor.h"
#endif

#if defined(_WIN32)
#include "WindowsMessageProcessing.h"


RWindowsEngine::RWindowsEngine():
	m_renderEngine(new DXRenderEngine()),
	m_EditorEngine(new EditorEngine())
{

}

RWindowsEngine::~RWindowsEngine()
{
	delete m_renderEngine;
}

int RWindowsEngine::PreInit(WinMainCommandParameters InParameters)
{
	ResizeScreenDelegate.AddFunction(this, &RWindowsEngine::OnResetSize);
	string logPath= PathHelper::RelativeToAbsolutePath(PathHelper::GetEngineLogsPath());
	//日志系统初始化
	init_log_system(logPath.c_str());
	Engine_Log("Init logSystem.");

	//渲染引擎初始化
	m_renderEngine->PreInit(InParameters);

	Engine_Log("PreInit Engine.");

	return 0;
}

int RWindowsEngine::Init(WinMainCommandParameters InParameters)
{
	m_Timer.Reset();

	InitWindows(InParameters);

	m_renderEngine->SetMianWindowsHandle(MianWindowsHandle);

	m_renderEngine->Init(InParameters);
	BUILD_OBJECT_PARAMETERS_BY_NO_COMPONENT(this);
	m_world = CreateObject<RWorld>(inObjectParam,new RWorld());
	m_renderEngine->m_World = m_world;
	Engine_Log("Init Engine.");
	return 0;
}

int RWindowsEngine::PostInit()
{
	Engine_Log("PostInit Engine.");

	m_renderEngine->PostInit();

	for (auto& Tmp : GRObjects)
	{
		Tmp->Init();
	}

	return 0;
}

//void RWindowsEngine::Tick(GameTimer& gt)
//{
//	m_Timer.Tick();
//	CalculateFrameStats();
//	for (auto& Temp : GRObjects)
//	{
//		if(Temp->IsTick())
//			Temp->Tick(gt);
//	}
//
//	if (m_world && m_world->GetCamera())
//	{
//		ViewportInfo pViewportInfo;
//		XMFLOAT3 pViewPosition = m_world->GetCamera()->GetPosition();
//		pViewportInfo.ViewportPosition = XMFLOAT4(pViewPosition.x, pViewPosition.y, pViewPosition.z, 1.f);
//		pViewportInfo.ProjectMatrix= m_world->GetCamera()->GetProjectMatrix();
//		pViewportInfo.ViewMatrix = m_world->GetCamera()->GetViewMatrix();
//		m_renderEngine->UpdateCalculations(gt, pViewportInfo);
//	}
//
//	m_renderEngine->Tick(gt);
//}

void RWindowsEngine::Tick()
{
	m_Timer.Tick();
	CalculateFrameStats();
	for (auto& Temp : GRObjects)
	{
		if (Temp->IsTick())
			Temp->Tick(m_Timer);
	}

	if (m_world && m_world->GetCamera())
	{
		ViewportInfo pViewportInfo;
		XMFLOAT3 pViewPosition = m_world->GetCamera()->GetPosition();
		pViewportInfo.ViewportPosition = XMFLOAT4(pViewPosition.x, pViewPosition.y, pViewPosition.z, 1.f);
		pViewportInfo.ProjectMatrix = m_world->GetCamera()->GetProjectMatrix();
		pViewportInfo.ViewMatrix = m_world->GetCamera()->GetViewMatrix();
		m_renderEngine->UpdateCalculations(m_Timer, pViewportInfo);
	}

	m_renderEngine->Tick(m_Timer);
}


void RWindowsEngine::OnResetSize(int width, int height)
{
	m_renderEngine->OnResetSize(width, height);
	m_EditorEngine->OnResetSize(width, height);
}

int RWindowsEngine::PreExit()
{
	m_renderEngine->PreExit();

	Engine_Log("PreExit Engine.");
	return 0;
}

int RWindowsEngine::Exit()
{
	m_renderEngine->PreExit();

	Engine_Log("Exit Engine.");
	return 0;
}

int RWindowsEngine::PostExit()
{
	m_renderEngine->PostExit();

	Engine_Log("PostExit Engine.");
	return 0;
}

bool RWindowsEngine::InitWindows(WinMainCommandParameters InParameters)
{
	//注册窗口
	WNDCLASSEX WindowsClass;
	WindowsClass.cbSize = sizeof(WNDCLASSEX);//该对象实际占用多大内存
	WindowsClass.cbClsExtra = 0;//是否需要额外空间
	WindowsClass.cbWndExtra = 0;//是否需要额外内存
	WindowsClass.hbrBackground = nullptr;//如果有设置哪就是GDI擦除
	WindowsClass.hCursor = LoadCursor(NULL, IDC_ARROW);//设置一个箭头光标
	WindowsClass.hIcon = nullptr; //应用程序放在磁盘上显示的图标
	WindowsClass.hIconSm = NULL;//应用程序显示在左上角的图标
	WindowsClass.hInstance = InParameters.HInstance; //窗口实例
	WindowsClass.lpszClassName = L"REngine";//窗口名字
	WindowsClass.lpszMenuName = nullptr;//
	WindowsClass.style = CS_VREDRAW | CS_HREDRAW;//怎么绘制窗口 垂直和水平重绘
	WindowsClass.lpfnWndProc = EngineWindowProc;//消息处理函数

	//注册窗口
	ATOM RegisterAtom = RegisterClassEx(&WindowsClass);
	if (!RegisterAtom)
	{
		Engine_Log_Error("Register windows Failer.");
		MessageBox(NULL, L"Register windows Failer.", L"Error", MB_OK);
	}

	RECT Rect = { 0,0,EngineRenderConfig::GetRenderConfig()->ScreenWidth,EngineRenderConfig::GetRenderConfig()->ScreenHeight };

	//@rect 适口
	//WS_OVERLAPPEDWINDOW 适口风格
	//NULL 没有菜单
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, NULL);

	int WindowWidth = Rect.right - Rect.left;
	int WindowHight = Rect.bottom - Rect.top;

	MianWindowsHandle = CreateWindow(
		L"REngine", // 窗口名称
		mMainWndCaption.c_str(),//会显示在窗口的标题栏上去
		WS_OVERLAPPEDWINDOW, //窗口风格
		0, 0,//窗口的坐标
		WindowWidth, WindowHight,//
		NULL, //副窗口句柄
		nullptr, //菜单句柄
		InParameters.HInstance,//窗口实例
		NULL);//
	if (!MianWindowsHandle)
	{
		Engine_Log_Error("Create Windows Failed.");
		MessageBox(0, L"Create Windows Failed.", 0, 0);
		return false;
	}

	//显示窗口
	ShowWindow(MianWindowsHandle, SW_SHOW);

	//窗口刷新
	UpdateWindow(MianWindowsHandle);

	Engine_Log("Init Windows.");
}

void RWindowsEngine::CalculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;
	float totalTime = m_Timer.TotalTime();
	// Compute averages over one second period.
	if ((m_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		wstring fpsStr = to_wstring(fps);
		wstring mspfStr = to_wstring(mspf);

		wstring windowText = mMainWndCaption +
			L"    fps: " + fpsStr +
			L"   mspf: " + mspfStr;

		SetWindowText(MianWindowsHandle, windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}


RMeshManage* RWindowsEngine::GetMeshManage()
{
	return m_renderEngine->GetMeshManage();
}

RLightManage* RWindowsEngine::GetLightManage()
{
	return m_renderEngine->GetLightManage();
}

RTextureManage* RWindowsEngine::GetTextureManage()
{
	return m_renderEngine->GetTextureManage();
}

#endif