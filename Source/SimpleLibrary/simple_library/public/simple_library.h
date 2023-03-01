﻿#pragma once

#ifdef CLOSE_DISABLE_DEBUG_INFOR
#pragma warning(disable:4267)//“参数”：从“xx”转换为“xx”，可能会丢失数据
#pragma warning(disable:4311)// 类型转换：指针从“您的ptr*”截断为“DWORD”
#pragma warning(disable:4244)// 从“xx”转换为“xx”，可能会丢失数据
#pragma warning(disable:4309)// 常数值截断
#pragma warning(disable:4305)//“参数”：从“int”截断为“u\u short”
#pragma warning(disable:4133)// function”：不兼容的类型-从“char[260]”到“LPWSTR”
#pragma warning(disable:4090)//“正在初始化”：不同的“const”限定符
#pragma warning(disable:4013)//“XXX”未定义；假设外部返回int
#pragma warning(disable:4251)// 以后开启当前状态检查dll情况
#pragma warning(disable:4717)// 在所有控制路径上递归，函数将导致运行时堆栈溢出
#pragma warning(disable:4099)// 首先使用“struct”看到的类型名称现在使用“class”看到
#pragma warning(disable:4018)// ：“<”：有符号/无符号不匹配
#endif // DEBUG

//core minimal
#include "simple_core_minimal/simple_c_guid/simple_guid.h"
#include "simple_core_minimal/simple_c_path/simple_path.h"
#include "simple_core_minimal/simple_c_windows/simple_c_windows_setting.h"
#include "simple_core_minimal/simple_c_windows/simple_c_windows_register.h"
#include "simple_core_minimal/simple_c_helper_file/simple_file_helper.h"
#include "simple_core_minimal/simple_c_time/simple_c_time.h"

//core
#include "simple_core_minimal/simple_c_core/simple_c_string_algorithm/string_algorithm.h"


//application 
#include "simple_c_log/simple_c_log.h"

//Delegate
#include "simple_delegate/simple_delegate.h"

//math
#include "simple_math/simple_core_math.h"

//image
#include "simple_image/simple_image.h"

