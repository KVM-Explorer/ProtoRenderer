#pragma once
#include <string>
#include <string_view>
namespace ProtoEngine::Core::Utils {
std::string wstring2string(const std::wstring &wstr);
std::wstring string2wstring(const std::string &str);
} // namespace ProtoEngine::Core::Utils