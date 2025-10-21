#include "Launcher.h"
#include "Engine/Core/Core.h"
#include <windows.h>
#include <shellapi.h> // 需要包含这个头文件以使用 CommandLineToArgvW

bool ParseCmdLineArgs(std::vector<std::wstring> &args)
{
    int argc = 0;
    // 1. 调用 API 将命令行解析为 Unicode 字符串数组
    LPWSTR *argvw = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (argvw == nullptr) {
        // 解析失败，返回空向量
        return {};
    }
    // 2. 将 C 风格的数组转换为更安全的 C++ vector
    args.reserve(argc); // 优化性能，预分配内存
    for (int i = 0; i < argc; ++i) {
        args.push_back(argvw[i]);
    }

    // 4. 打印解析后的参数（可选）
    for (size_t i = 0; i < args.size(); ++i) {
        // 注意：因为是宽字符，所以需要用 wprintf 或 std::wcout
        wprintf(L"Argument %zu: %s\n", i, args[i].c_str());
    }

    // 5. 关键步骤：释放由 CommandLineToArgvW 分配的内存！
    //    这是一个常见的内存泄漏点。
    LocalFree(argvw);
    return true;
}

namespace ProtoEngine {

std::unique_ptr<Launcher> Launcher::m_Instance = nullptr;


void Launcher::Run()
{
    // LoadingInit();//
    PreInit();    // Load Param From config file, command line arguments, app set args
    Init();       // Init RHI & Windows
    PostInit();   // Load Assets
    EngineLoop(); // Main Loop
    Shutdown();
}

void Launcher::PreInit()
{
    // parameter load order:
    // 1. config file
    // 2. command line arguments
    // 3. app set args
    // 4. default values

    // Step1: Load config file
    if (/* config file exists */ 1) {
    }

    // Step2: Load command line arguments
    std::vector<std::wstring> args;
    if (ParseCmdLineArgs(args)) {
    }

    // Step3: Load app set args

    if (1 /*Exist Program Set Args */) {
        // ...
    }

    // Setp4: Create Windows
    m_WindowInstance = WindowBuilder::New()
                           .Width(1280)
                           .Height(720)
                           .Title("ProtoRenderer")
                           .Build();

    // Step5: Init RHI
}

void Launcher::Init()
{
    // Bind Pipeline/RHI & Windows
}

void Launcher::PostInit()
{
}

void Launcher::EngineLoop()
{
    while (Core::GEngine.IsRunning) {
        // Update
        // Render
    }
}

void Launcher::Shutdown()
{
    // Shutdown RHI
    // Shutdown Windows
}

} // namespace ProtoEngine
