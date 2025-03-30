#include <directx/d3dx12_root_signature.h>
#include "ProtoEngine/RHI/DX12/GPULayout/Shader.h"
#include "ProtoEngine/Core/Core.h"

namespace ProtoEngine::rhi::dx12 {

DXGI_FORMAT maskToFormat(uint32 mask)
{
    switch (mask) {
    case 1:
        return DXGI_FORMAT_R32_FLOAT;
    case 3:
        return DXGI_FORMAT_R32G32_FLOAT;
    case 7:
        return DXGI_FORMAT_R32G32B32_FLOAT;
    case 15:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
    default:
        PE_THROW("Invalid mask");
    }
}

Shader::~Shader()
{
}

Shader::Shader(ShaderInfo &info) :
    m_Desc(info.desc),
    m_Reflection(info.reflection),
    m_Type(info.type)
{
    if (info.blob == nullptr) {
        PE_THROW("Invalid shader blob");
    } else {
        m_Blob = info.blob->GetBufferPointer();
        m_Size = info.blob->GetBufferSize();
    }
}

D3D12_INPUT_LAYOUT_DESC Shader::GetInputLayout()
{
    if (m_Type != ShaderType::Vertex) PE_THROW("Invalid shader type");

    semanticNames.resize(m_Desc.InputParameters);
    inputElementDescs.resize(m_Desc.InputParameters);

    for (auto i = 0; i < m_Desc.InputParameters; ++i) {
        D3D12_SIGNATURE_PARAMETER_DESC param{};
        m_Reflection->GetInputParameterDesc(i, &param);

        semanticNames[i] = std::string(param.SemanticName);

        auto &desc = inputElementDescs[i];
        desc.SemanticName = semanticNames[i].c_str();
        desc.SemanticIndex = param.SemanticIndex;
        desc.Format = maskToFormat(param.Mask);

        desc.InputSlot = 0;
        desc.AlignedByteOffset = D3D12_APPEND_ALIGNED_ELEMENT;
        desc.InputSlotClass = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
        desc.InstanceDataStepRate = 0;
    }

    return {
        .pInputElementDescs = inputElementDescs.data(),
        .NumElements = static_cast<uint32>(inputElementDescs.size())};
}

D3D12_SHADER_BYTECODE Shader::GetShaderByteCode()
{
    return {
        .pShaderBytecode = m_Blob,
        .BytecodeLength = m_Size};
}

void Shader::GetRootSignature(ID3D12Device *device, ComPtr<ID3D12RootSignature> &rootSignature)
{
    std::vector<D3D12_ROOT_PARAMETER1> rootParams{};
    std::vector<D3D12_STATIC_SAMPLER_DESC> staticSamplers{};
    CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC desc{};

    for (int i = 0; i < m_Desc.BoundResources; i++) {
        D3D12_SHADER_INPUT_BIND_DESC desc;
        m_Reflection->GetResourceBindingDesc(i, &desc);
        switch (desc.Type) {
        case D3D_SIT_CBUFFER:
            break;
        case D3D_SIT_TEXTURE:
            break;
        case D3D_SIT_SAMPLER:
            break;
        default:
            PE_THROW("resource type parsing not implemented");
        }
    }

    D3D12_ROOT_SIGNATURE_FLAGS flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
    if (m_Type == ShaderType::Vertex) {
        flags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
    }
    desc.Init_1_1(rootParams.size(),
                  rootParams.data(),
                  staticSamplers.size(),
                  staticSamplers.data(),
                  flags);

    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    PE_ASSERT(D3DX12SerializeVersionedRootSignature(&desc, D3D_ROOT_SIGNATURE_VERSION_1_1, &signature, &error));
    PE_ASSERT(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature)));

    if (error) {
        PE_LOG_ERROR("Error creating root signature: {}", (char *)error->GetBufferPointer());
    }

    return;
}

} // namespace ProtoEngine::rhi::dx12