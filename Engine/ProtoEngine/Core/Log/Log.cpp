#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include "ProtoEngine/Core/Log/Log.h"
#include <spdlog/async.h>

using namespace ProtoEngine::Core;

std::unique_ptr<Log> Log::Instance = nullptr;

spdlog::level::level_enum GetLevel(LogLevel level)
{
    spdlog::level::level_enum logLevel;
    switch (level) {
    case LogLevel::Trace: logLevel = spdlog::level::trace; break;
    case LogLevel::Debug: logLevel = spdlog::level::debug; break;
    case LogLevel::Info: logLevel = spdlog::level::info; break;
    case LogLevel::Warning: logLevel = spdlog::level::warn; break;
    case LogLevel::Error: logLevel = spdlog::level::err; break;
    case LogLevel::Critical: logLevel = spdlog::level::critical; break;
    case LogLevel::Off: logLevel = spdlog::level::off; break;
    }
    return logLevel;
}

Log::Log() :
    Log(LogLevel::Trace) {}
Log::Log(LogLevel level)
{
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("ProtoEngine.txt", 1024 * 1024 * 10, 3)); // 10MB max file size, 3 rotated files

    logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    logSinks[1]->set_pattern("[%T] [%l] %n: %v");

    auto logLevel = GetLevel(level);

    CoreLogger = std::make_shared<spdlog::logger>("ProtoEngine", begin(logSinks), end(logSinks));
    spdlog::register_logger(CoreLogger);
    CoreLogger->set_level(logLevel);
    CoreLogger->flush_on(logLevel);

    ClientLogger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
    spdlog::register_logger(ClientLogger);
    ClientLogger->set_level(logLevel);
    ClientLogger->flush_on(logLevel);
}

Log::~Log(){
    
}
void Log::SetLevel(LogLevel level)
{
    auto logLevel = GetLevel(level);
    if (Instance == nullptr) {
        Instance = std::make_unique<Log>(level);
    } else {
        Instance->CoreLogger->set_level(logLevel);
        Instance->ClientLogger->set_level(logLevel);
    }
}

spdlog::logger &Log::GetCore()
{
    if (Instance == nullptr) {
        Instance = std::make_unique<Log>();
    }
    return *Instance->CoreLogger;
}

spdlog::logger &Log::GetClient()
{
    if (Instance == nullptr) {
        Instance = std::make_unique<Log>();
    }
    return *Instance->ClientLogger;
}
