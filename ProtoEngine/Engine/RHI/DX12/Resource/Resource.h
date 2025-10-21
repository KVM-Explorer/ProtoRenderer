#pragma once

#include <stdafx.h>

namespace ProtoEngine::rhi::dx12 {

class Resource {
public:
    Resource();
    ~Resource();

protected:
    ComPtr<ID3D12Resource> m_Resource;
    

};

} // namespace ProtoEngine::rhi::dx12