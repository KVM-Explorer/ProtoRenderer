#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <functional>
#include <string_view>
#include <map>
#include <variant>
#include <type_traits>
#include <optional>
#include <tuple>

using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using int32 = int32_t;
using int64 = int64_t;

#define RHI_DX12

#ifdef RHI_DX12

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <directx/d3dx12.h>
#include <dxgi1_6.h>
#include <wrl.h>

using Microsoft::WRL::ComPtr;

#endif

#ifdef _DEBUG
#define PE_SHADER_DEBUG 1
#else
#define PE_SHADER_DEBUG 0
#endif