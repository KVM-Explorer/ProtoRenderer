#pragma once

#include <stdafx.h>
#include <dxcapi.h>
#include <d3d12shader.h>
#include "Engine/RHI/DX12/GPULayout/Shader.h"

namespace ProtoEngine::rhi::dx12 {

// Shader 实例的全部反射信息和Blob
struct ShaderData {
    ComPtr<IDxcBlob> blob;
    D3D12_SHADER_DESC desc;
    ComPtr<ID3D12ShaderReflection> reflection;
    ShaderType type;
};

class ShaderCompiler {
public:
    ShaderCompiler();
    ~ShaderCompiler();

    static std::shared_ptr<ShaderCompiler> GetInstance();
    void Release();

    Shader Compile(const std::string &shaderPath, const std::string &entryPoint, const std::string &target);

    // Shader Hash
    static uint64 GetShaderHash(const std::string &shaderPath, const std::string &entryPoint, const std::string &target);

private:
    static std::shared_ptr<ShaderCompiler> m_Instance;
    ComPtr<IDxcUtils> m_Utils;
    ComPtr<IDxcCompiler3> m_Compiler;
    ComPtr<IDxcIncludeHandler> m_IncludeHandler;

    std::unordered_map<uint64, ShaderData> m_ShaderData;
};

} // namespace ProtoEngine::rhi::dx12