#include "ProtoEngine/RHI/DX12/Runtime/Sync.h"
#include "ProtoEngine/RHI/DX12/Runtime/GPUContext.h"
#include "ProtoEngine/Core/Core.h"
namespace ProtoEngine::rhi::dx12 {

FrameSyncPoint::FrameSyncPoint(ID3D12Device *device)
{
    ComPtr<ID3D12Fence> fence;
    ThrowIfFailed(device->CreateFence(0,
                                      D3D12_FENCE_FLAG_NONE,
                                      IID_PPV_ARGS(&m_Fence)));

    m_FenceValue = 1;
}

void FrameSyncPoint::Signal(GPUContext *context)
{
    context->GfxQueue->Signal(m_Fence.Get(), m_FenceValue);
    m_FenceValue++;
}

void FrameSyncPoint::Wait()
{
    if (m_Fence->GetCompletedValue() < m_FenceValue) {
        HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        m_Fence->SetEventOnCompletion(m_FenceValue - 1, event);
        WaitForSingleObject(event, INFINITE);
    }
}

} // namespace ProtoEngine::rhi::dx12