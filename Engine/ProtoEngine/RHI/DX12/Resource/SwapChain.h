#pragma once
#include <stdafx.h>
#include "ProtoEngine/RHI/DX12/Runtime/GPUContext.h"
namespace ProtoEngine::rhi::dx12 {

class SwapChain {
public:
    SwapChain(GPUContext &, uint32 width, uint32 height);
    ~SwapChain();

    void Resize(uint32 &width, uint32 &height);

    IDXGISwapChain3 *Get() const { return m_SwapChain.Get(); }

    std::tuple<uint32, uint32> GetCurrentRT() const { return {m_RTVHandles[m_CurrentFrameIndex], m_ResourceIndices[m_CurrentFrameIndex]}; }
    uint32 GetCurrentFrameIndex() const { return m_CurrentFrameIndex; }
    void MoveNextFrame() { m_CurrentFrameIndex = (m_CurrentFrameIndex + 1) % m_FrameCount; }
    static uint32 GetFrameCount() { return m_FrameCount; }
    uint32 GetWidth() const { return m_Width; }

    void Present();

private:
    ComPtr<IDXGISwapChain3> m_SwapChain;
    uint32 m_CurrentFrameIndex = 0;
    static const uint32 m_FrameCount = 2;
    std::array<uint32, m_FrameCount> m_RTVHandles;
    std::array<uint32, m_FrameCount> m_ResourceIndices;
    uint32 m_Width;
    uint32 m_Height;
    GPUContext &m_Context;

    void CreateSwapChain();
};

} // namespace ProtoEngine::rhi::dx12