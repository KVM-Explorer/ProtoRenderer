#include "ProtoEngine/RHI/DX12/Resource/DescriptorHeap.h"

namespace ProtoEngine::rhi::dx12 {

DescriptorHeap::DescriptorHeap(ID3D12Device *device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32 numDescriptors, bool isShaderVisible) :
    m_Type(type),
    m_DescriptorRange(numDescriptors),
    m_Device(device),
    m_ShaderVisible(isShaderVisible),
    m_DescriptorSize(device->GetDescriptorHandleIncrementSize(type))

{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = numDescriptors;
    heapDesc.Type = type;
    heapDesc.Flags = isShaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&m_Heap));

    m_CPUAddress = m_Heap->GetCPUDescriptorHandleForHeapStart();
    m_GPUAddress = m_Heap->GetGPUDescriptorHandleForHeapStart();
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUHandle(uint32 index) const
{
    return CD3DX12_CPU_DESCRIPTOR_HANDLE(m_CPUAddress, index, m_DescriptorSize);
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGPUHandle(uint32 index) const
{
    return CD3DX12_GPU_DESCRIPTOR_HANDLE(m_GPUAddress, index, m_DescriptorSize);
}

RTVHeap::RTVHeap(ID3D12Device *device, uint32 numDescriptors) :
    DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, numDescriptors, false)
{}

uint32 RTVHeap::Add(ID3D12Resource *resource, std::optional<D3D12_RENDER_TARGET_VIEW_DESC> &descInfo)
{
    // Alloc New
    uint32 index = m_DescriptorCount;
    m_DescriptorCount++;

    if (descInfo.has_value()) {
        m_Device->CreateRenderTargetView(resource, &descInfo.value(), GetCPUHandle(index));
    } else {
        D3D12_RENDER_TARGET_VIEW_DESC desc;
        desc.Format = resource->GetDesc().Format;
        desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipSlice = 0;
        desc.Texture2D.PlaneSlice = 0;
        m_Device->CreateRenderTargetView(resource, &desc, GetCPUHandle(index));
    }

    return index;
}

DSVHeap::DSVHeap(ID3D12Device *device, uint32 numDescriptors) :
    DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, numDescriptors, false)
{
}

SRVHeap::SRVHeap(ID3D12Device *device, uint32 numDescriptors, bool shaderVisible) :
    DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, numDescriptors, shaderVisible) {}

UAVHeap::UAVHeap(ID3D12Device *device, uint32 numDescriptors, bool shaderVisible) :
    DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, numDescriptors, shaderVisible) {}

} // namespace ProtoEngine::rhi::dx12