#pragma once
#include <string>
#include <string_view>
namespace ProtoEngine::rhi::interface{
class Device {
public:
    Device() = default;
    virtual ~Device() = default;

    virtual void Init() = 0;
    virtual void Shutdown() = 0;

    const std::string_view GetName() const
    {
        return m_Name;
    }

protected:
    std::string m_Name;
};
} // namespace ProtoEngine::rhi