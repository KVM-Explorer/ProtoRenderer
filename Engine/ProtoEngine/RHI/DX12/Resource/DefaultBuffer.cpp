#include "ProtoEngine/RHI/DX12/Resource/DefaultBuffer.h"
#include "ProtoEngine/Core/Utils/Exception.h"

namespace ProtoEngine::rhi::dx12 {

DefaultBuffer::DefaultBuffer(ID3D12Device *device, uint64 size, std::string_view name) :
    Buffer(name)

{
    if (name.empty()) {
        static uint64 count = 0;
        name = "DefaultBuffer" + std::to_string(count++);
        SetName(name);
    }
    Init(device);
}

DefaultBuffer::~DefaultBuffer() {}

void DefaultBuffer::Init(ID3D12Device *device)
{
    D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(m_Size);

    ThrowIfFailed(device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&m_Resource)));
}

} // namespace ProtoEngine::rhi::dx12