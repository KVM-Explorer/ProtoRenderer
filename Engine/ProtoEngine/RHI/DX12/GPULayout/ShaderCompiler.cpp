#include "ProtoEngine/RHI/DX12/GPULayout/ShaderCompiler.h"
#include "ProtoEngine/Core/Core.h"
namespace ProtoEngine::rhi::dx12 {

std::shared_ptr<ShaderCompiler> ShaderCompiler::m_Instance = nullptr;

ShaderType GetShaderType(const std::string &entryPoint)
{
    if (entryPoint.find("VS") != std::string::npos) {
        return ShaderType::Vertex;
    } else if (entryPoint.find("PS") != std::string::npos) {
        return ShaderType::Pixel;
    } else if (entryPoint.find("CS") != std::string::npos) {
        return ShaderType::Compute;
    } else if (entryPoint.find("GS") != std::string::npos) {
        return ShaderType::Geometry;
    } else if (entryPoint.find("HS") != std::string::npos) {
        return ShaderType::Hull;
    } else if (entryPoint.find("DS") != std::string::npos) {
        return ShaderType::Domain;
    }
    PE_THROW("Invalid shader type");
}

ShaderCompiler::ShaderCompiler()
{
    ::DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_Utils));
    ::DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m_Compiler));
    m_Utils->CreateDefaultIncludeHandler(&m_IncludeHandler);
}

ShaderCompiler::~ShaderCompiler()
{
    m_Utils->Release();
    m_Compiler->Release();
}

std::shared_ptr<ShaderCompiler> ShaderCompiler::GetInstance()
{
    if (m_Instance == nullptr) {
        m_Instance = std::make_shared<ShaderCompiler>();
    }
    return m_Instance;
}

Shader ShaderCompiler::Compile(const std::string &shaderPath, const std::string &entryPoint, const std::string &target)
{
    PE_LOG_DEBUG("Compiling shader...");

    auto entryPointWStr = Core::Utils::string2wstring(entryPoint);
    auto targetWStr = Core::Utils::string2wstring(target);
    auto shaderPathWStr = Core::Utils::string2wstring(shaderPath);

    std::vector<LPCWCHAR> compilationArguments = {
        L"-E",
        entryPointWStr.c_str(),
        L"-T",
        targetWStr.c_str(),
        DXC_ARG_PACK_MATRIX_ROW_MAJOR,
        DXC_ARG_WARNINGS_ARE_ERRORS,
        DXC_ARG_ALL_RESOURCES_BOUND,
    };

    if constexpr(PE_SHADER_DEBUG) {
        compilationArguments.push_back(DXC_ARG_DEBUG);
        compilationArguments.push_back(DXC_ARG_SKIP_OPTIMIZATIONS);
    } else {
        compilationArguments.push_back(DXC_ARG_OPTIMIZATION_LEVEL3);
    }

    ComPtr<IDxcBlobEncoding> sourceBlob;
    PE_ASSERT(m_Utils->LoadFile(shaderPathWStr.c_str(), nullptr, &sourceBlob));

    DxcBuffer sourceBuffer{};
    sourceBuffer.Ptr = sourceBlob->GetBufferPointer();
    sourceBuffer.Size = sourceBlob->GetBufferSize();
    sourceBuffer.Encoding = 0;

    ComPtr<IDxcResult> result;
    auto hr = m_Compiler->Compile(&sourceBuffer, compilationArguments.data(), static_cast<UINT32>(compilationArguments.size()), m_IncludeHandler.Get(), IID_PPV_ARGS(&result));

    if (FAILED(hr)) {
        PE_LOG_ERROR("Failed to compile shader: {}", shaderPath);
    }

    ComPtr<IDxcBlobUtf8> errors;
    result->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr);
    if (errors && errors->GetStringLength() > 0) {
        PE_LOG_ERROR("Shader compilation error: {}", errors->GetStringPointer());
        PE_THROW("Shader compilation error");
    }

    ComPtr<IDxcBlob> reflectionBlob;
    result->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionBlob), nullptr);

    const DxcBuffer reflectionBuffer = {reflectionBlob->GetBufferPointer(), reflectionBlob->GetBufferSize(), 0};

    ComPtr<ID3D12ShaderReflection> reflection{};
    m_Utils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&reflection));

    D3D12_SHADER_DESC shaderDesc;
    reflection->GetDesc(&shaderDesc);

    PE_LOG_INFO("Shader compiled: {}", shaderPath);

    ComPtr<IDxcBlob> shaderBlob;
    result->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
    m_Blobs.push_back(std::move(shaderBlob));

    ShaderInfo info{
        shaderDesc,
        reflection.Get(),
        m_Blobs.back().Get(),
        GetShaderType(entryPoint),
    };

    return Shader(info);
}

} // namespace ProtoEngine::rhi::dx12