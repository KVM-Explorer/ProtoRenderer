#pragma once
#include <stdafx.h>
namespace ProtoEngine {
class App {
public:
    App(uint32 width, uint32 height, const std::string &name) :
        m_Width(width), m_Height(height), m_Name(name) {}
    virtual ~App() {};

public:
    virtual void Init() = 0;
    virtual void Shutdown() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void AfterTick() = 0;

    HWND m_Handle = nullptr;
    uint32 m_Width = 0;
    uint32 m_Height = 0;
    std::string m_Name;
};
} // namespace ProtoEngine