#pragma once
#include "stdafx.h"
#include "ProtoEngine/RHI/Interface/IDevice.h"

namespace ProtoEngine::rhi::dx12 {

class Device : public rhi::IDevice {
public:
    Device(int adapterIndex = 0);
    ~Device();

    void Init() override;

    ID3D12Device *Get() const { return m_Device.Get(); }
    IDXGIFactory6 *GetFactory() const { return m_Factory.Get(); }

private:
    static ComPtr<IDXGIFactory6> m_Factory;
    ComPtr<ID3D12Device6> m_Device;
};

} // namespace ProtoEngine::rhi::dx12