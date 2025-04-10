#include "ProtoEngine/Resource/DataCenter/ShaderContainer.h"
#include "ProtoEngine/Core/Log/Log.h"
#include "ProtoEngine/RHI/DX12/GPULayout/ShaderCompiler.h"

namespace ProtoEngine::resource {

ShaderContainer *ShaderContainer::GetInstance()
{
    if (!m_Instance) {
        m_Instance = std::make_shared<ShaderContainer>();
    }
    return m_Instance.get();
}

void ShaderContainer::Register(std::string name, std::shared_ptr<rhi::dx12::Shader> shader)
{
    if (m_ShaderNames.find(name) != m_ShaderNames.end()) {
        PE_LOG_ERROR("Shader already registered");
    }

    PE_LOG_INFO("Shader {} registered", name);
}

} // namespace ProtoEngine::resource