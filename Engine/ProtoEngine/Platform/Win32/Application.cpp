#include "ProtoEngine/Platform/Win32/Application.h"
#include "ProtoEngine/Core/Utils/Exception.h"
#include "ProtoEngine/Core/Log/Log.h"
namespace ProtoEngine::Platform::Win32 {

static Application *s_Instance = nullptr;

LRESULT CALLBACK Win32WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    App *app = reinterpret_cast<App *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (uMsg) {
    case WM_CREATE: {
        // Save the App* passed in to CreateWindow.
        LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        return 0;
    }
    case WM_DESTROY: // 处理窗口关闭事件
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: // 处理窗口重绘事件
        app->Update();
        app->Render();
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

Application *Application::Get()
{
    using namespace Core::Utils;
    if (s_Instance == nullptr) {
        PE_THROW("Application not created");
    }
    return s_Instance;
}

Application::Application(uint32 width, uint32 height, const std::string_view &name) :
    m_Width(width), m_Height(height), m_Name(name)
{
    if (s_Instance == nullptr) {
        s_Instance = this;
    } else {
        PE_THROW("Application already created");
    }
}

Application::~Application() {}

void Application::Run(std::shared_ptr<App> app)
{
    PE_LOG_INFO("Windows Start Create");
    WNDCLASSEX wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Win32WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = m_Name.data();

    if (!RegisterClassEx(&wcex)) {
        PE_THROW("Failed to register window class");
    }

    m_Handle = CreateWindowEx(0, m_Name.data(), m_Name.data(),
                              WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              m_Width, m_Height,
                              nullptr, nullptr,
                              GetModuleHandle(nullptr),
                              app.get());

    if (!m_Handle) {
        PE_THROW("Failed to create window");
    }

    app->Init();

    ShowWindow(m_Handle, SW_SHOWDEFAULT);
    UpdateWindow(m_Handle);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    app->Shutdown();
}

} // namespace ProtoEngine::Platform::Win32