#pragma once
#include <stdafx.h>
#include "Engine/Render/IRenderPipeline.h"

class Window {
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    IRenderPipeline *m_Pipeline;
    HWND m_hwnd;
    void Init(HWND hwnd);

public:
    friend class WindowBuilder;
    Window() {};
    ~Window() {};

    HWND GetHwnd() const { return m_hwnd; }
    void BindRenderPipeline(IRenderPipeline *pipeline) { m_Pipeline = pipeline; }
};

class WindowBuilder {
public:
    static WindowBuilder &New();

    WindowBuilder(const WindowBuilder &) = delete;
    WindowBuilder &operator=(const WindowBuilder &) = delete;

    WindowBuilder &Title(const std::string &title);
    WindowBuilder &Width(int width)
    {
        m_Width = width;
        return *this;
    }
    WindowBuilder &Height(int height)
    {
        m_Height = height;
        return *this;
    }
    std::shared_ptr<Window> Build();

private:
    WindowBuilder(){};

    std::wstring m_Title;
    int m_Width;
    int m_Height;
    HWND m_hwnd;
};
