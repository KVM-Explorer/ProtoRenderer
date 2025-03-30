
#include "ProtoEngine/RHI/DX12/Runtime/Device.h"
#include "ProtoEngine/Core/Utils/Exception.h"
#include "ProtoEngine/Core/Utils/StringUtils.h"
#include "ProtoEngine/Core/Log/Log.h"
#include <dxgidebug.h>
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
        PE_THROW("Failed to create D3D12 device");
    }
    device.As(&this->m_Device);
    auto name = std::wstring(desc.Description);
    m_Name = Core::Utils::wstring2string(name);

    PE_LOG_INFO("D3D12 device created: {}", m_Name);
}

Device::~Device()
{
}

void Device::Init()
{
    UINT dxgiFactoryFlags = 0;

    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
    }

    ComPtr<ID3D12Debug1> debug1;
    debugController->QueryInterface(IID_PPV_ARGS(&debug1));
    debug1->SetEnableGPUBasedValidation(true);
    debug1->SetEnableSynchronizedCommandQueueValidation(true);

    dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;

    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_Factory));
}

} // namespace ProtoEngine::rhi::dx12