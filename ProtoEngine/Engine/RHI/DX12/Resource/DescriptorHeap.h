#pragma once

#include <stdafx.h>
#include <directx/d3dx12_core.h>
namespace ProtoEngine::rhi::dx12 {

class DescriptorHeap {
public:
    DescriptorHeap(ID3D12Device *device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors, bool shaderVisible);
    ~DescriptorHeap() {};

    D3D12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(uint32 index) const;
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(uint32 index) const;
    ID3D12DescriptorHeap *GetHeap() const { return m_Heap.Get(); };

protected:
    ID3D12Device *m_Device;
    ComPtr<ID3D12DescriptorHeap> m_Heap;
    D3D12_DESCRIPTOR_HEAP_TYPE m_Type;
    uint32 m_DescriptorRange;
    uint32 m_DescriptorCount = 0;
    bool m_ShaderVisible;
    uint32 m_DescriptorSize;
    D3D12_CPU_DESCRIPTOR_HANDLE m_CPUAddress;
    D3D12_GPU_DESCRIPTOR_HANDLE m_GPUAddress;
};

class RTVHeap : public DescriptorHeap {
public:
    RTVHeap(ID3D12Device *device, uint32 numDescriptors);
    uint32 Add(ID3D12Resource *resource, std::optional<D3D12_RENDER_TARGET_VIEW_DESC> &descInfo);
};

class DSVHeap : public DescriptorHeap {
public:
    DSVHeap(ID3D12Device *device, uint32 numDescriptors);

    // uint32 Add(ID3D12Resource *resource);
};

class SRVHeap : public DescriptorHeap {
public:
    SRVHeap(ID3D12Device *device, uint32 numDescriptors, bool shaderVisible);

    // uint32 Add(ID3D12Resource *resource);
    uint32 Add(ID3D12Resource *resource, D3D12_SHADER_RESOURCE_VIEW_DESC &desc);
};

class UAVHeap : public DescriptorHeap {
public:
    UAVHeap(ID3D12Device *device, uint32 numDescriptors, bool shaderVisible);

    // uint32 Add(ID3D12Resource *resource);
};

} // namespace ProtoEngine::rhi::dx12