#include "spdlog/spdlog.h"
#include "Core/Log/Log.h"

using namespace ProtoEngine::Core;

std::unique_ptr<Log> Log::log = nullptr;

Log::Log()
{
}

Log &Log::Get()
{
    if (log == nullptr) {
        log = std::make_unique<Log>();
    }
    return *log;
}

void Log::Debug(const char *format, ...)
{
}

void Log::Info(const char *format, ...)
{
}

void Log::Warning(const char *format, ...)
{
}

void Log::Error(const char *format, ...)
{
}
