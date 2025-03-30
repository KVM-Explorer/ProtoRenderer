#pragma once
#include <stdafx.h>
#include <spdlog/spdlog.h>

namespace ProtoEngine::Core {

enum class LogLevel {
    Trace = 0,
    Debug = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Critical = 5,
    Off = 6
};

class Log {
public:
    static spdlog::logger &GetCore();
    static spdlog::logger &GetClient();

    void SetLevel(LogLevel level);
    Log();
    Log(LogLevel level);
    ~Log();

private:
    static std::unique_ptr<Log> Instance;
    std::shared_ptr<spdlog::logger> CoreLogger;
    std::shared_ptr<spdlog::logger> ClientLogger;
};

#define PE_LOG_DEBUG(...) ProtoEngine::Core::Log::GetCore().debug(__VA_ARGS__)
#define PE_LOG_INFO(...) ProtoEngine::Core::Log::GetCore().info(__VA_ARGS__)
#define PE_LOG_WARNING(...) ProtoEngine::Core::Log::GetCore().warn(__VA_ARGS__)
#define PE_LOG_ERROR(...) ProtoEngine::Core::Log::GetCore().error(__VA_ARGS__)

#define APP_LOG_DEBUG(...) ProtoEngine::Core::Log::GetClient().debug(__VA_ARGS__)
#define APP_LOG_INFO(...) ProtoEngine::Core::Log::GetClient().info(__VA_ARGS__)
#define APP_LOG_WARNING(...) ProtoEngine::Core::Log::GetClient().warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ProtoEngine::Core::Log::GetClient().error(__VA_ARGS__)

} // namespace ProtoEngine::Core
