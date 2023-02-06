#pragma once
#include"../../EngineMacro.h"

#if EDITOR_ENGINE
#include"../../../Editor/Log/LogSystem.h"
#endif

#if defined(_WIN32)
#include "simple_library/public/simple_library.h"

#if EDITOR_ENGINE
#define Engine_Log(format,...)\
log_log(format,__VA_ARGS__)\
EditorLogSystem::Get()->AddLog(format,__VA_ARGS__);
#else
#define Engine_Log(format,...)\
log_log(format,__VA_ARGS__)
#endif

#if EDITOR_ENGINE
#define Engine_Log_Success(format,...)\
log_success(format,__VA_ARGS__)\
EditorLogSystem::Get()->AddSuccess(format,__VA_ARGS__);
#else
#define Engine_Log_Success(format,...)\
log_success(format,__VA_ARGS__)
#endif

#if EDITOR_ENGINE
#define Engine_Log_Error(format,...)\
log_error(format,__VA_ARGS__)\
EditorLogSystem::Get()->AddError(format,__VA_ARGS__);
#else
#define Engine_Log_Error(format,...)\
log_error(format,__VA_ARGS__)
#endif

#if EDITOR_ENGINE
#define Engine_Log_Warning(format,...)\
log_warning(format,__VA_ARGS__)\
EditorLogSystem::Get()->AddWarning(format,__VA_ARGS__);
#else
#define Engine_Log_Warning(format,...)\
log_warning(format,__VA_ARGS__)
#endif

#elif 0


#elif 0

#define Engine_log(format,...) 
#define Engine_Log_Success(format,...) 
#define Engine_Log_Error(format,...) 
#define Engine_Log_Warning(format,...) 

#endif