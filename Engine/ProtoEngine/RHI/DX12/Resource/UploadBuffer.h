#pragma once
#include <stdafx.h>
#include "ProtoEngine/RHI/DX12/Resource/Buffer.h"

namespace ProtoEngine::rhi::dx12 {

class UploadBuffer : public Buffer {
public:
    UploadBuffer(ID3D12Device *device, UINT64 size, std::string_view name = "");
    ~UploadBuffer();
    UploadBuffer(const UploadBuffer &rhs) = delete;
    UploadBuffer &operator=(const UploadBuffer &rhs) = delete;

    void CopyData(const void *data, UINT64 size, UINT64 offset = 0);

private:
    void Init(ID3D12Device *device) override;

    UINT64 m_Size;
    void *m_MappedData;
};
} // namespace ProtoEngine::rhi::dx12