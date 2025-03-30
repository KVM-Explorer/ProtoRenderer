#pragma once
#include <stdafx.h>
namespace ProtoEngine::rhi::dx12 {

class GPUInputLayout {
public:
    virtual ~GPUInputLayout()
    {
        m_Signature.Reset();
        m_PSO.Reset();
    };

    virtual void Init(ID3D12Device *device) = 0;

    ID3D12RootSignature *GetSignature() const { return m_Signature.Get(); }
    ID3D12PipelineState *GetPSO() const { return m_PSO.Get(); }

protected:
    ComPtr<ID3D12RootSignature> m_Signature;
    ComPtr<ID3D12PipelineState> m_PSO;
};

} // namespace ProtoEngine::rhi::dx12