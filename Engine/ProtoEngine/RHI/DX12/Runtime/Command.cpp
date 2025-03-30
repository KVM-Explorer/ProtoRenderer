#include "ProtoEngine/RHI/DX12/Runtime/Command.h"
#include "ProtoEngine/Core/Core.h"
#include "GPUContext.h"
#include "directx/d3dx12_core.h"
#include "ProtoEngine/RHI/DX12/Resource/ResourceAllocator.h"
namespace ProtoEngine::rhi::dx12 {

Command::~Command()
{
    m_Pool->Free(m_Type, m_PoolIndex);
    // TODO: Free After Resource Sync
}
void Command::BindGPULayout(GPUInputLayout *layout)
{
    auto pso = layout->GetPSO();
    auto signature = layout->GetSignature();
    m_CommandList->SetPipelineState(pso);
    m_CommandList->SetGraphicsRootSignature(signature);

    // auto allocator = ResourceAllocator::GetInstance();
    // auto heaps = std::to_array({allocator->RTV()->GetHeap()});

    // m_CommandList->SetDescriptorHeaps(heaps.size(), heaps.data());
    m_CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Command::SetScreenView(const ScreenRect &viewPort, const ScreenRect &scissor)
{
    CD3DX12_VIEWPORT viewport = CD3DX12_VIEWPORT(viewPort.TopLeftX, viewPort.TopLeftY, viewPort.Width, viewPort.Height);
    m_CommandList->RSSetViewports(1, &viewport);
    CD3DX12_RECT rect = CD3DX12_RECT(scissor.TopLeftX, scissor.TopLeftY, scissor.Width, scissor.Height);
    m_CommandList->RSSetScissorRects(1, &rect);
}

void Command::ClearRT(std::vector<uint32> renderTargets, std::optional<uint32> depthTarget)
{
    auto allocator = ResourceAllocator::GetInstance();
    auto rtvHeap = allocator->RTV();
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvHandles;
    for (auto target : renderTargets) {
        auto rtvHandle = rtvHeap->GetCPUHandle(target);
        rtvHandles.push_back(rtvHandle);
    }

    if (depthTarget.has_value()) {
        auto dsvHeap = allocator->DSV();
        auto dsvHandle = dsvHeap->GetCPUHandle(depthTarget.value());
        m_CommandList->OMSetRenderTargets(rtvHandles.size(), rtvHandles.data(), false, &dsvHandle);
    } else {
        m_CommandList->OMSetRenderTargets(rtvHandles.size(), rtvHandles.data(), false, nullptr);
    }

    const float m_ClearColor[4] = {0.0f, 0.2f, 0.4f, 1.0f};

    if (depthTarget.has_value()) {
        auto dsvHeap = allocator->DSV();
        m_CommandList->ClearDepthStencilView(dsvHeap->GetCPUHandle(depthTarget.value()), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
    }

    for (auto target : rtvHandles) {
        m_CommandList->ClearRenderTargetView(target, m_ClearColor, 0, nullptr);
    }
}

void Command::DrawCall(D3D12_VERTEX_BUFFER_VIEW vertexBufferView, D3D12_INDEX_BUFFER_VIEW indexBufferView)
{
    m_CommandList->IASetVertexBuffers(0, 1, &vertexBufferView);
    m_CommandList->IASetIndexBuffer(&indexBufferView);
    m_CommandList->DrawIndexedInstanced(3, 1, 0, 0, 0);
}

void Command::ResourceBarrier(std::vector<D3D12_RESOURCE_BARRIER> barriers)
{
    m_CommandList->ResourceBarrier(static_cast<uint32>(barriers.size()), barriers.data());
}

CommandPool::CommandPool(GPUContext &context) :
    m_Context(context)
{
    auto device = context.m_Device->Get();
}

Command CommandPool::Allocate(CommandType type, uint32 taskOrder)
{
    if (!m_FreeIndices[static_cast<uint32>(type)].empty()) {
        auto index = m_FreeIndices[static_cast<uint32>(type)].front();
        m_FreeIndices[static_cast<uint32>(type)].pop();

        if (m_UsedIndices[static_cast<uint32>(type)][index]) {
            PE_THROW("CommandPool index is already used");
        }
        m_UsedIndices[static_cast<uint32>(type)][index] = true;

        auto &allocator = m_Allocators[static_cast<uint32>(type)][index];
        allocator->Reset();

        auto cmdList = GetCommandList(allocator.Get(), static_cast<D3D12_COMMAND_LIST_TYPE>(type));
        // Bind cmdList to Command
        return Command(index, type, cmdList, this);
    }

    PE_LOG_INFO("CommandPool is empty, try to expand Command Allocator");

    auto device = m_Context.m_Device->Get();
    D3D12_COMMAND_LIST_TYPE listType;
    ID3D12CommandQueue *queue;
    switch (type) {
    case CommandType::Graphics:
        listType = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queue = m_Context.GfxQueue.Get();
        break;
    case CommandType::Compute:
        listType = D3D12_COMMAND_LIST_TYPE_COMPUTE;
        queue = m_Context.GfxQueue.Get();
        break;
    case CommandType::Copy:
        listType = D3D12_COMMAND_LIST_TYPE_COPY;
        queue = m_Context.CopyQueue.Get();
        break;
    default:
        PE_THROW("Invalid Command Type");
        break;
    }

    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Type = listType;
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.NodeMask = 0;

    ComPtr<ID3D12CommandAllocator> allocator;
    ComPtr<ID3D12GraphicsCommandList> commandList;

    ThrowIfFailed(device->CreateCommandAllocator(listType, IID_PPV_ARGS(&allocator)));
    auto cmdList = GetCommandList(allocator.Get(), listType);

    auto index = static_cast<uint32>(m_Allocators[static_cast<uint32>(type)].size());
    m_Allocators[static_cast<uint32>(type)].push_back(allocator);
    m_UsedIndices[static_cast<uint32>(type)][index] = true;

    return Command(index, type, cmdList, this);
}

void CommandPool::Free(CommandType type, uint32 index)
{
    if (!m_UsedIndices[static_cast<uint32>(type)][index]) PE_THROW("Trying to free an unused command");
    m_UsedIndices[static_cast<uint32>(type)][index] = false;

    m_FreeIndices[static_cast<uint32>(type)].push(index);
}
void CommandPool::EndFrame()
{
    PE_LOG_DEBUG("CommandPool EndFrame Swap Free and Used CommandList");
    std::swap(m_FreeCommands, m_UsedCommands);
}

ID3D12GraphicsCommandList *CommandPool::GetCommandList(ID3D12CommandAllocator *allocator, D3D12_COMMAND_LIST_TYPE type)
{
    if (!m_FreeCommands.empty()) {
        auto cmdList = m_FreeCommands.front();
        m_FreeCommands.pop();
        cmdList->Reset(allocator, nullptr);
        // cmdList->Close();

        m_UsedCommands.push(cmdList);

        return cmdList.Get();
    } else {
        ComPtr<ID3D12GraphicsCommandList> cmdList;
        auto device = m_Context.m_Device->Get();
        ThrowIfFailed(device->CreateCommandList(0, type, allocator, nullptr, IID_PPV_ARGS(&cmdList)));
        // ThrowIfFailed(cmdList->Close());

        m_UsedCommands.push(cmdList);
        return cmdList.Get();
    }
}

} // namespace ProtoEngine::rhi::dx12