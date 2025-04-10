#pragma once

#include "stdafx.h"
#include "ProtoEngine/RHI/DX12/GPULayout/Shader.h"
namespace ProtoEngine::resource {

class ShaderContainer {
public:
    ShaderContainer *GetInstance();

    void Register(std::string name, std::shared_ptr<rhi::dx12::Shader> shader);
    std::shared_ptr<rhi::dx12::Shader> Get(std::string name);
    void Clear();

private:
    static std::shared_ptr<ShaderContainer> m_Instance;
    std::unordered_map<uint64, std::shared_ptr<rhi::dx12::Shader>> m_ShaderInstances;
    std::unordered_map<std::string, uint64> m_ShaderNames;
};
} // namespace ProtoEngine::resource