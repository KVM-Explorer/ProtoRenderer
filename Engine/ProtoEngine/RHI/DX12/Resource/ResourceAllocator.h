#pragma once
#include <stdafx.h>
#include "ProtoEngine/RHI/DX12/Resource/DescriptorHeap.h"
namespace ProtoEngine::rhi::dx12 {

struct AllocInfo {
    uint32 resourceIndex;
    std::optional<uint32> SRV;
    std::optional<uint32> UAV;
    std::optional<uint32> RTV;
    std::optional<uint32> DSV;
};

enum ResourceUsage : uint32 {
    RTV = 1,
    DSV = (RTV << 1),
    SRV = (DSV << 1),
    UAV = (SRV << 1),
};

struct ResourceInfo {
    std::string name;
    uint32 usage;
    std::optional<D3D12_RENDER_TARGET_VIEW_DESC> rtvDesc = std::nullopt;
    std::optional<D3D12_DEPTH_STENCIL_VIEW_DESC> dsvDesc = std::nullopt;
    std::optional<D3D12_SHADER_RESOURCE_VIEW_DESC> srvDesc = std::nullopt;
    std::optional<D3D12_UNORDERED_ACCESS_VIEW_DESC> uavDesc = std::nullopt;
};

class ResourceAllocator {
public:
    static ResourceAllocator *GetInstance();

    void Init(ID3D12Device *device);

    AllocInfo RegisterResource(ComPtr<ID3D12Resource> resource, ResourceInfo &info);
    ID3D12Resource *GetResource(uint32 index) const;
    RTVHeap *RTV() { return m_RTVHeap.get(); }
    DSVHeap *DSV() { return m_DSVHeap.get(); }

private:
    static std::unique_ptr<ResourceAllocator> m_Instance;
    std::vector<ComPtr<ID3D12Resource>> m_Resources;

    std::unique_ptr<RTVHeap> m_RTVHeap;
    std::unique_ptr<DSVHeap> m_DSVHeap;
    std::unique_ptr<SRVHeap> m_SRVHeap;
    std::unique_ptr<UAVHeap> m_UAVHeap;
};
} // namespace ProtoEngine::rhi::dx12