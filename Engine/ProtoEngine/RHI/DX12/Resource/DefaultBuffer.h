#pragma once

#include "ProtoEngine/RHI/DX12/Resource/Buffer.h"

namespace ProtoEngine::rhi::dx12 {

class DefaultBuffer : public Buffer {
public:
    DefaultBuffer(ID3D12Device *device, uint64 size,std::string_view name);
    ~DefaultBuffer();

    void Init(ID3D12Device *device) override;
private:
    uint64 m_Size;
};
} // namespace ProtoEngine::rhi::dx12