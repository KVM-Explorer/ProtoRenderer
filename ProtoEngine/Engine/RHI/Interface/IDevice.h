#pragma once
#include <stdafx.h>
namespace ProtoEngine::rhi{
class IDevice {
public:
    IDevice() = default;
    virtual ~IDevice() = default;

    virtual void Init() = 0;

    const std::string_view GetName() const
    {
        return m_Name;
    }

protected:
    std::string m_Name;
};
} // namespace ProtoEngine::rhi