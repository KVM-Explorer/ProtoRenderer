#include "Engine/Core/Utils/Exception.h"
#include "Engine/Core/Log.h"
#include <format>
namespace ProtoEngine::Core::Utils {

Exception::Exception(const std::string &message, const char *file, int line) :
    m_Message(message)
{
    m_Message += std::format("\nFile: {}\nLine: {}", file, line);
    PE_LOG_ERROR(m_Message.c_str());
}

const char *Exception::what() const noexcept
{
    return m_Message.c_str();
}
} // namespace ProtoEngine::Core::Utils