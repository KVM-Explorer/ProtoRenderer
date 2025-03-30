#pragma once

#include <stdafx.h>
#include <dxcapi.h>
#include <d3d12shader.h>

namespace ProtoEngine::rhi::dx12 {

enum class ShaderType {
    Vertex,
    Pixel,
    Compute,
    Geometry,
    Hull,
    Domain
};

struct ShaderInfo {
    D3D12_SHADER_DESC desc;
    ID3D12ShaderReflection *reflection;
    ComPtr<IDxcBlob> blob;
    ShaderType type;
};

class Shader {
public:
    Shader(ShaderInfo &info);
    ~Shader();

    D3D12_INPUT_LAYOUT_DESC GetInputLayout();
    D3D12_SHADER_BYTECODE GetShaderByteCode() ;
    void GetRootSignature(ID3D12Device *device, ComPtr<ID3D12RootSignature> &rootSignature);

private:
    D3D12_SHADER_DESC m_Desc;
    ID3D12ShaderReflection *m_Reflection;
    void *m_Blob;
    size_t m_Size;
    ShaderType m_Type;

    std::vector<std::string> semanticNames;
    std::vector<D3D12_INPUT_ELEMENT_DESC> inputElementDescs;
};

}; // namespace ProtoEngine::rhi::dx12