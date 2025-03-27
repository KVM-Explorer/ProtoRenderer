
#include "RHI/Runtime/DX12/Device.h"
#include <stdexcept>
#include "Core/Utils/StringUtils.h"
namespace ProtoEngine::rhi::dx12 {
ComPtr<IDXGIFactory6> Device::m_Factory = nullptr;

Device::Device(int adapterIndex)

{
    if (m_Factory == nullptr) Init();

    ComPtr<IDXGIAdapter1> adapter = nullptr;
    ComPtr<ID3D12Device> device = nullptr;
    DXGI_ADAPTER_DESC1 desc;
    for (auto i = 0; m_Factory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
        adapter->GetDesc1(&desc);
        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
        if (i != adapterIndex) continue;

        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_1;
        if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), featureLevel, IID_PPV_ARGS(&device)))) {
            break;
        }
    }

    if (device == nullptr) {
        throw std::runtime_error("Failed to create D3D12 device");
    }
    device.As(&this->m_Device);
    auto name = std::wstring(desc.Description);
    m_Name = Core::Utils::wstring2string(name);
}

Device::~Device()
{
    Shutdown();
}

void Device::Init()
{
    UINT dxgiFactoryFlags = 0;

    // debugController
    // ID3D12Debug1 debugController;
    // if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
    //     debugController->EnableDebugLayer();
    // }

    // ID3D12Debug1 debug1;
    // debugController->QueryInterface(IID_PPV_ARGS(&debug1));
    // debug1->SetEnableGPUBasedValidation(true);

    dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_Factory));
}

} // namespace ProtoEngine::rhi::dx12