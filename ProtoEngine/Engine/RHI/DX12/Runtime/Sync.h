#pragma once
#include <stdafx.h>
#include <directx/d3dx12_core.h>
namespace ProtoEngine::rhi::dx12 {
class GPUContext;
class FrameSyncPoint {
public:
    FrameSyncPoint(ID3D12Device *device);
    void Signal(GPUContext *context);
    void Wait();

private:
    ComPtr<ID3D12Fence> m_Fence;
    UINT64 m_FenceValue;
};

class ResourceSyncPoint {
public:

    void Signal(GPUContext *context);
    void Wait();

};

} // namespace ProtoEngine::rhi::dx12