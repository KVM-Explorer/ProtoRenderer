#include "RHI/Runtime/DX12/GPUContext.h"
#include <stdexcept>

namespace ProtoEngine::rhi::dx12 {

GPUContext::GPUContext(int adapterIndex)
{
    m_Device = std::make_unique<Device>(adapterIndex);
    Init();
}

GPUContext::~GPUContext()
{
    GfxQueue = nullptr;
    CopyQueue = nullptr;
    m_Device->Shutdown();
}

void GPUContext::Init()
{
    auto device = m_Device->Get();

    D3D12_COMMAND_QUEUE_DESC gfxQueueDesc = {};
    gfxQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    gfxQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    gfxQueueDesc.NodeMask = 0;

    device->CreateCommandQueue(&gfxQueueDesc, IID_PPV_ARGS(&GfxQueue));

    D3D12_COMMAND_QUEUE_DESC copyQueueDesc = {};
    copyQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
    copyQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    copyQueueDesc.NodeMask = 0;

    device->CreateCommandQueue(&copyQueueDesc, IID_PPV_ARGS(&CopyQueue));
}

void GPUContext::Submit(std::vector<Command> commands)
{
    if(commands.empty()) throw std::runtime_error("Commands are empty");
    auto device = m_Device->Get();
    auto gfxQueue = GfxQueue.Get();
    auto copyQueue = CopyQueue.Get();

    std::vector<ID3D12CommandList *> cmdLists;

    for (auto &command : commands) {
        cmdLists.push_back(command.Get());
    }

    switch (commands[0].Type()) {
    case CommandType::Graphics: {
        gfxQueue->ExecuteCommandLists(static_cast<UINT>(cmdLists.size()), cmdLists.data());
        break;
    }
    case CommandType::Compute: {
        copyQueue->ExecuteCommandLists(static_cast<UINT>(cmdLists.size()), cmdLists.data());
        break;
    }
    case CommandType::Copy: {
        copyQueue->ExecuteCommandLists(static_cast<UINT>(cmdLists.size()), cmdLists.data());
    }
    }
}

} // namespace ProtoEngine::rhi::dx12