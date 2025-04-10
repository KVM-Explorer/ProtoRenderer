#pragma once
#include "ProtoEngine/RHI/DX12/Runtime/Device.h"
#include "ProtoEngine/RHI/DX12/Runtime/Command.h"
namespace ProtoEngine::rhi::dx12 {

class GPUContext {
public:
    GPUContext(int adapterIndex = 0);
    virtual ~GPUContext();

    void Submit(std::vector<Command*> commands);
    void WaitForIdle();
    ID3D12Device *GetDevice() const { return m_Device->Get(); }

protected:
    void Init();

private:
    friend class SwapChain;
    friend class CommandPool;
    friend class FrameSyncPoint;

    std::unique_ptr<Device> m_Device;
    ComPtr<ID3D12CommandQueue> GfxQueue;

    ComPtr<ID3D12CommandQueue> CopyQueue;
};

} // namespace ProtoEngine::rhi::dx12