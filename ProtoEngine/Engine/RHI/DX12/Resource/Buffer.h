#pragma once
#include <stdafx.h>
#include <format>
namespace ProtoEngine::rhi::dx12 {

class Buffer {
public:
    ID3D12Resource *Get() const { return m_Resource.Get(); }
    std::string_view GetName() const { return m_Name; }
protected:
    Buffer(std::string_view name) :
        m_ID(BufferID++),
        m_Name("Buffer" + std::to_string(m_ID))
    {
        if (!name.empty()) m_Name = std::format("Buffer{}_{}", m_Name, name);
    }

    virtual void Init(ID3D12Device *device) = 0;

protected:
    ComPtr<ID3D12Resource> m_Resource;
    void SetName(std::string_view name){m_Name = name;}
private:
    static inline uint64 BufferID = 0;
    uint64 m_ID;
    std::string m_Name;
};

} // namespace ProtoEngine::rhi::dx12