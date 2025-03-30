#include <stdafx.h>
#include <winbase.h>
#include "ProtoEngine/Platform/Win32/Application.h"
#include "ProtoEngine/Engine.h"
#include "ProtoEngine/App.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Load Param from Command Line & Config File

    // Init Engine
    ProtoEngine::Engine engine;
    engine.Init();
    auto app = engine.GetApp();

    // Init Platform
    ProtoEngine::Platform::Win32::Application windows(app->m_Width, app->m_Height, app->m_Name);
    windows.Run(app);
    return 0;
}