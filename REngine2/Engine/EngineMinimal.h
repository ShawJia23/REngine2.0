﻿#pragma once

#include"Debug/EngineLog.h"
#include "../simple_library/public/simple_library.h"
#include "Debug/Log/SimpleLog.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include"Render/DX12/d3dx12.h"
#include"Math/RMath.h"
#include <wrl.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

extern class REngine* Engine;