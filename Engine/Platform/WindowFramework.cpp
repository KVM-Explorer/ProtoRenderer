#include "Platform/WindowFramework.h"

WindowBuilder &WindowBuilder::New()
{
    return *(new WindowBuilder());
}

WindowBuilder &WindowBuilder::Title(const std::string &title)
{
    m_Title = std::wstring(title.begin(), title.end());
    return *this;
}

std::shared_ptr<Window> WindowBuilder::Build()
{
    WNDCLASSEXW wc = {0};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = m_Title.c_str();
    if (!RegisterClassExW(&wc)) {
        return NULL;
    }
    RECT wr = {0, 0, m_Width, m_Height};
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

    auto window = make_shared<Window>();

    m_hwnd = CreateWindowExW(
        0, m_Title.c_str(), m_Title.c_str(),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left, wr.bottom - wr.top,
        NULL, NULL, GetModuleHandle(NULL), window.get() // 关键点：将this指针传入
    );

    if (!m_hwnd) {
        return nullptr;
    }

    window->Init(m_hwnd);
    return window;
}

void Window::Init(HWND hwnd)
{
    m_hwnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // 当没有窗口消息时，执行渲染循环
            static steady_clock::time_point lastTime = steady_clock::now();
            auto currentTime = steady_clock::now();
            auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);
            lastTime = currentTime;
            m_Pipeline->Update(deltaTime);
            m_Pipeline->Render();
        }
    }
}

// --- Static Window Procedure ---
LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Window *pThis = nullptr;
    if (uMsg == WM_NCCREATE) {
        // 在窗口创建时，从lParam中恢复this指针并存储
        CREATESTRUCT *pCreate = (CREATESTRUCT *)lParam;
        pThis = (Window *)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
    } else {
        // 在后续消息中，从用户数据中取回this指针
        pThis = (Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (!pThis) {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    switch (uMsg) {
    // case WM_SIZE: {
    //     int width = LOWORD(lParam);
    //     int height = HIWORD(lParam);
    //     pThis->m_Pipeline->OnResize(width, height);
    //     return 0;
    // }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        /* 可利用ps.rcPaint获取更新渲染区域，实现局部重绘，避免被其他窗口遮挡部分的开销，但是实际情况是采用这种方法往
         往需要重构对应的渲染资源往往会导致性能问题，因而其更常用于非频繁更新的场景，同时BeginPaint会意味程序开始
         处理脏数据区域，避免OS无限发送WM_PAINT,同时需要注意配合EndPaint使用
         WM_PAINT的数据驱动源如下，并且其本身作为一个低优先级刷奶昔，只有当不存在更高优先级任务时系统才会合成，因而频率不可控
            1. 用户输入（如键盘、鼠标事件）
            2. 窗口变化（如窗口大小改变、窗口遮挡等）
            3. 定时器（但是一般精度比较低）
        */
        HDC hdc = BeginPaint(hwnd, &ps);
        // pThis->m_Pipeline->Update(0.0f);
        // pThis->m_Pipeline->Render();
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
        // 可在此处添加更多消息处理，如键盘、鼠标输入，并转发给Component
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}