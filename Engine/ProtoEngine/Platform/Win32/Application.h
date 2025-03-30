#pragma once
#include <stdafx.h>
#include "ProtoEngine/App.h"
namespace ProtoEngine::Platform::Win32 {
class Application {
public:
    Application(uint32 width, uint32 height, const std::string_view &name);
    virtual ~Application();

    void Run(std::shared_ptr<App> app);

    HWND GetHandle() const { return m_Handle; };

    static Application *Get();

private:
    static std::unique_ptr<Application> Instance;
    HWND m_Handle = nullptr;
    uint32 m_Width = 0;
    uint32 m_Height = 0;
    std::string m_Name;
};
} // namespace ProtoEngine::Platform::Win32
