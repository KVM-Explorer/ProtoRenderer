#pragma once

#include <exception>
#include <string>

namespace ProtoEngine::Core::Utils {

class Exception : public std::exception {
public:
    Exception(const std::string &message);
    const char *what() const noexcept override;

private:
    std::string m_Message;
};

} // namespace ProtoEngine::Core::Utils