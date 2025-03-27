#pragma once
#include "RHI/Runtime/DX12/Device.h"
#include "RHI/Runtime/DX12/Command.h"
namespace ProtoEngine::rhi::dx12 {

class GPUContext {
public:
    GPUContext(int adapterIndex = 0);
    virtual ~GPUContext();

    void Submit(std::vector<Command> commands);

protected:
    void Init();

private:
    std::unique_ptr<Device> m_Device;
    ComPtr<ID3D12CommandQueue> GfxQueue;
    ComPtr<ID3D12CommandQueue> CopyQueue;
};

} // namespace ProtoEngine::rhi::dx12