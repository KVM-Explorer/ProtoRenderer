#pragma once
#include "stdafx.h"
namespace ProtoEngine::Core {
class Log {
public:
    static Log &Get();
    Log();
    ~Log();

    void Debug(const char *format, ...);
    void Info(const char *format, ...);
    void Warning(const char *format, ...);
    void Error(const char *format, ...);

protected:
private:
    static std::unique_ptr<Log> log;
};

static void Debug(const char *format, ...);
static void Info(const char *format, ...);
static void Warning(const char *format, ...);
static void Error(const char *format, ...);
} // namespace ProtoEngine::Core
