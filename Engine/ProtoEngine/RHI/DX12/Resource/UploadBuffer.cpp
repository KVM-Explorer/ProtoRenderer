#include "ProtoEngine/RHI/DX12/Resource/UploadBuffer.h"
#include "ProtoEngine/Core/Core.h"

namespace ProtoEngine::rhi::dx12 {

UploadBuffer::UploadBuffer(ID3D12Device *device, UINT64 size, std::string_view name) :
    Buffer(name),
    m_Size(size)
{
    Init(device);
}

UploadBuffer::~UploadBuffer() {}

void UploadBuffer::Init(ID3D12Device *device)
{
    D3D12_HEAP_PROPERTIES heapProp = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    D3D12_RESOURCE_DESC resDesc = CD3DX12_RESOURCE_DESC::Buffer(m_Size);

    ThrowIfFailed(device->CreateCommittedResource(
        &heapProp,
        D3D12_HEAP_FLAG_NONE,
        &resDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&m_Resource)));

    ThrowIfFailed(m_Resource->Map(0, nullptr, &m_MappedData));
}

void UploadBuffer::CopyData(const void *data, UINT64 size, UINT64 offset)
{
    memcpy(reinterpret_cast<uint8 *>(m_MappedData) + offset, data, size);
}

}; // namespace ProtoEngine::rhi::dx12