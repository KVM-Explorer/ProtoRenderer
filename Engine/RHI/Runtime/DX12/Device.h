#pragma once
#include "RHI/Runtime/Interface/Device.h"
using DeviceInterface = ProtoEngine::rhi::interface::Device;
#include "stdafx.h"

namespace ProtoEngine::rhi::dx12 {

class Device : public DeviceInterface {
public:
    Device(int adapterIndex = 0);
    ~Device();

    void Init() override;
    void Shutdown() override;

    ID3D12Device *Get() const { return m_Device.Get(); }

private:
    static ComPtr<IDXGIFactory6> m_Factory;
    ComPtr<ID3D12Device6> m_Device;
};

} // namespace ProtoEngine::rhi::dx12