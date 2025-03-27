#include "Core/Utils/Exception.h"
#include "Core/Log/Log.h"
namespace ProtoEngine::Core::Utils {

Exception::Exception(const std::string &message) :
    m_Message(message)
{
    std::string msg = message;
    Error("{}",msg.c_str());
}

const char *Exception::what() const noexcept
{
    return m_Message.c_str();
}
} // namespace ProtoEngine::Core::Utils