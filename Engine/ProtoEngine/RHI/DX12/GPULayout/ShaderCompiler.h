#pragma once

#include <stdafx.h>
#include <dxcapi.h>
#include <d3d12shader.h>
#include "ProtoEngine/RHI/DX12/GPULayout/Shader.h"

namespace ProtoEngine::rhi::dx12 {

class ShaderCompiler {
public:
    ShaderCompiler();
    ~ShaderCompiler();

    static std::shared_ptr<ShaderCompiler> GetInstance();

    Shader Compile(const std::string &shaderPath, const std::string &entryPoint, const std::string &target) ;
private:
    static std::shared_ptr<ShaderCompiler> m_Instance;
    ComPtr<IDxcUtils> m_Utils;
    ComPtr<IDxcCompiler3> m_Compiler;
    ComPtr<IDxcIncludeHandler> m_IncludeHandler;

    std::vector<ComPtr<IDxcBlob>> m_Blobs;
};

} // namespace ProtoEngine::rhi::dx12