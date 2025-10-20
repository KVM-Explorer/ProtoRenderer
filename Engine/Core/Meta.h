#pragma once
#include <stdafx.h>

namespace ProtoEngine::Core {

struct EngineContext {
    std::wstring AppName = L"ProtoRenderer";
    int Width = 1280;
    int Height = 720;
    HANDLE WindowHandle = nullptr;
    bool IsRunning = true;
};

extern EngineContext GEngine;

} // namespace ProtoEngine::Core
