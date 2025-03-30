#include "ProtoEngine/RHI/DX12/Resource/ResourceAllocator.h"
#include "ProtoEngine/Core/Log/Log.h"
#include "ProtoEngine/Core/Core.h"

namespace ProtoEngine::rhi::dx12 {

std::unique_ptr<ResourceAllocator> ResourceAllocator::m_Instance = nullptr;

ResourceAllocator *ResourceAllocator::GetInstance()
{
    if (m_Instance == nullptr) {
        m_Instance = std::make_unique<ResourceAllocator>();
    }
    return m_Instance.get();
}

void ResourceAllocator::Init(ID3D12Device *device)
{
    m_RTVHeap = std::make_unique<RTVHeap>(device, 1024);
    m_DSVHeap = std::make_unique<DSVHeap>(device, 1024);
    m_SRVHeap = std::make_unique<SRVHeap>(device, 1024, true);
    m_UAVHeap = std::make_unique<UAVHeap>(device, 1024, false);
}

ID3D12Resource *ResourceAllocator::GetResource(uint32 index) const
{
    if (index >= m_Resources.size()) {
        PE_LOG_ERROR("Resource index out of range");
    }
    return m_Resources[index].Get();
}

AllocInfo ResourceAllocator::RegisterResource(ComPtr<ID3D12Resource> resource, ResourceInfo &info)
{
    AllocInfo ret;

    ret.resourceIndex = m_Resources.size();

    resource->SetName(Core::Utils::string2wstring(info.name).c_str());
    if (info.usage | static_cast<uint32>(ResourceUsage::RTV)) {
        ret.RTV = m_RTVHeap->Add(resource.Get(), info.rtvDesc);
    }

    // if (info.dsvDesc.has_value()) {
    //     ret.DSV = m_DSVHeap->Add(resource.Get(), info.dsvDesc.value());
    // }

    // if (info.srvDesc.has_value()) {
    //     ret.SRV = m_SRVHeap->Add(resource.Get(), info.srvDesc.value());
    // }

    // if (info.uavDesc.has_value()) {
    //     ret.UAV = m_UAVHeap->Add(resource.Get(), info.uavDesc.value());
    // }

    m_Resources.push_back(resource);
    // TODO Relase Before SwapChain Release
    return ret;
}

} // namespace ProtoEngine::rhi::dx12