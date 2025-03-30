#pragma once

#include <exception>
#include <string>

namespace ProtoEngine::Core::Utils {

class Exception : public std::exception {
public:
    Exception(const std::string &message, const char *file, int line);
    const char *what() const noexcept override;

private:
    std::string m_Message;
};

#define PE_THROW(message) throw ProtoEngine::Core::Utils::Exception(message, __FILE__, __LINE__)

#define T(condition)          \
    if ((condition < 0)) {            \
        PE_THROW("Assertion failed"); \
    }

} // namespace ProtoEngine::Core::Utils