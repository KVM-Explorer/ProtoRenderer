#include "Core/Utils/StringUtils.h"

namespace ProtoEngine::Core::Utils {

std::string wstring2string(const std::wstring &wstr)
{
    return std::string(wstr.begin(), wstr.end());
}

std::wstring string2wstring(const std::string &str)
{
    return std::wstring(str.begin(), str.end());
}

} // namespace ProtoEngine::Core::Utils
