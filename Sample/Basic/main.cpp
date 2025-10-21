#include <iostream>
#include "Engine/Launcher.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ProtoEngine::Launcher::New()
        .Width(1280)
        .Height(720)
        .AppName("ProtoRenderer Basic Sample")
        .Run();
    return 0;
}