#pragma once
#include "Platform/WindowFramework.h"
#include "stdafx.h"
#include "Core/Meta.h"

namespace ProtoEngine {

struct LauncherArgs {
    std::optional<std::string> AppName;
    std::optional<int> Width;
    std::optional<int> Height;
};

/*
 * @brief Launcher is the entry point of the engine.
 * @detail parameter load order:
 * 1. config file
 * 2. command line arguments
 * 3. app set args
 * 4. default values
 *
 */
class Launcher {
public:
    static Launcher &New()
    {
        return GetInstance();
    }
    Launcher &AppName(const std::string &appName)
    {
        m_Args.AppName = appName;
        return *this;
    }

    Launcher &Width(int width)
    {
        m_Args.Width = width;
        return *this;
    }

    Launcher &Height(int height)
    {
        m_Args.Height = height;
        return *this;
    }

    void Run();

private:
    using EngineContext = ProtoEngine::Core::EngineContext;

    LauncherArgs m_Args{};
    shared_ptr<Window> m_WindowInstance;

    static std::unique_ptr<Launcher> m_Instance;

    static Launcher &GetInstance()
    {
        if (!m_Instance) {
            m_Instance = std::make_unique<Launcher>();
        }
        return *m_Instance;
    }

    void PreInit();
    void Init();
    void PostInit();

    void EngineLoop();

    void Shutdown();
};

}; // namespace ProtoEngine