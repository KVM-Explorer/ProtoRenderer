#pragma once
#include "Engine/RHI/DX12/GPULayout/Layout.h"
#include <stdafx.h>

namespace ProtoEngine::rhi::dx12 {

struct ScreenRect {
    float TopLeftX;
    float TopLeftY;
    float Width;
    float Height;

    ScreenRect(float topLeftX, float topLeftY, float width, float height) :
        TopLeftX(topLeftX), TopLeftY(topLeftY), Width(width), Height(height) {}
    ScreenRect(float width, float height) :
        TopLeftX(0), TopLeftY(0), Width(width), Height(height) {}
    ScreenRect() :
        TopLeftX(0), TopLeftY(0), Width(0), Height(0) {}
};

enum class CommandType {
    Graphics,
    Compute,
    Copy,
    TypeNum
};

class CommandPool;
class Command {
public:
    Command(uint32 poolIndex, CommandType type, ID3D12GraphicsCommandList *commandList, CommandPool *pool) :
        m_PoolIndex(poolIndex), m_Type(type),
        m_CommandList(commandList),
        m_Pool(pool)
    {}
    virtual ~Command();

    uint32 ID() const { return m_PoolIndex; }

    void SetScreenView(const ScreenRect &viewPort, const ScreenRect &scissor);
    void BindGPULayout(GPUInputLayout *layout);

    void ClearRT(std::vector<uint32> renderTargets, std::optional<uint32> depthTarget);

    void DrawCall(D3D12_VERTEX_BUFFER_VIEW vertexBufferView, D3D12_INDEX_BUFFER_VIEW indexBufferView);

    void ResourceBarrier(std::vector<D3D12_RESOURCE_BARRIER> barriers);
    CommandType Type() const { return m_Type; }
    ID3D12CommandList *Get() const { return m_CommandList; }

    void Upload(ID3D12Resource *dst, ID3D12Resource *src, uint64 size);

    void Begin() {}
    void End() { m_CommandList->Close(); }

private:
    uint32 m_TaskOrder;
    bool m_Recording = true;
    uint32 m_PoolIndex;
    CommandType m_Type;
    ID3D12GraphicsCommandList *m_CommandList;
    CommandPool *m_Pool;
};

class GPUContext;
class CommandPool {
public:
    struct AllocateInfo {
        uint32 PoolIndex;
        CommandType Type;
    };

    CommandPool(GPUContext &context);
    ~CommandPool() {};

    Command Allocate(CommandType type, uint32 taskOrder);
    void Free(CommandType type, uint32 index); // Free Allocator

    void BeginFrame();
    void EndFrame();

private:
    ID3D12GraphicsCommandList *GetCommandList(ID3D12CommandAllocator *allocator, CommandType type);

    GPUContext &m_Context;

    static constexpr uint32 m_TypeNum = static_cast<uint32>(CommandType::TypeNum);

    // Allocator
    std::array<std::queue<uint32>, m_TypeNum> m_FreeIndices;
    std::array<std::unordered_map<uint32, bool>, m_TypeNum> m_UsedIndices;
    std::array<std::vector<ComPtr<ID3D12CommandAllocator>>, m_TypeNum> m_Allocators; // 帧、并行数据

    // Command List
    std::array<std::queue<ComPtr<ID3D12GraphicsCommandList>>, m_TypeNum> m_FreeCommands;
    std::array<std::queue<ComPtr<ID3D12GraphicsCommandList>>, m_TypeNum> m_UsedCommands;
};

} // namespace ProtoEngine::rhi::dx12