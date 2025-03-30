#include "ProtoEngine/RHI/DX12/Resource/SwapChain.h"
#include "ProtoEngine/Core/Log/Log.h"
#include "ProtoEngine/Core/Utils/Exception.h"
#include "ProtoEngine/Platform/Win32/Application.h"
#include "ProtoEngine/RHI/DX12/Resource/ResourceAllocator.h"
namespace ProtoEngine::rhi::dx12 {

SwapChain::SwapChain(rhi::dx12::GPUContext &context, uint32 width, uint32 height) :
    m_Context(context),
    m_Width(width),
    m_Height(height)
{
    CreateSwapChain();
}

SwapChain::~SwapChain()
{
}

void SwapChain::CreateSwapChain()
{
    ComPtr<IDXGISwapChain1> swapchain1;
    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    swapchainDesc.Width = m_Width;
    swapchainDesc.Height = m_Height;
    swapchainDesc.BufferCount = m_FrameCount;
    swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    swapchainDesc.SampleDesc.Count = 1;

    auto factory = m_Context.m_Device->GetFactory();
    auto queue = m_Context.GfxQueue.Get();
    auto handle = ProtoEngine::Platform::Win32::Application::Get()->GetHandle();
    ThrowIfFailed(factory->CreateSwapChainForHwnd(queue, handle, &swapchainDesc, nullptr, nullptr, &swapchain1));
    swapchain1->QueryInterface(IID_PPV_ARGS(&m_SwapChain));
    ThrowIfFailed(factory->MakeWindowAssociation(handle, DXGI_MWA_NO_ALT_ENTER));
    ThrowIfFailed(swapchain1.As(&m_SwapChain));

    auto allocator = ResourceAllocator::GetInstance();
    for (int i = 0; i < m_FrameCount; i++) {
        ComPtr<ID3D12Resource> backBuffer;
        ThrowIfFailed(m_SwapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer)));
        ResourceInfo info;
        info.name = "BackBuffer" + std::to_string(i);
        info.usage = ResourceUsage::RTV;
        auto allocInfo = allocator->RegisterResource(backBuffer, info);
        m_RTVHandles[i] = allocInfo.RTV.value();
        m_ResourceIndices[i] = allocInfo.resourceIndex;
    }

    PE_LOG_INFO("SwapChain Created");
}

void SwapChain::Present()
{
    m_SwapChain->Present(0, 0);
}

void SwapChain::Resize(uint32 &width, uint32 &height)
{
    if (width == m_Width && height == m_Height) {
        return;
    }

    m_Width = width;
    m_Height = height;

    // for (int i = 0; i < m_FrameCount; i++) {
    //     m_backBuffers[i].reset();
    // }
    // TODO: Resize RTV

    PE_THROW("Not Implemented");

    DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
    DXGI_SWAP_CHAIN_DESC swapchainDescOld = {};
    m_SwapChain->GetDesc(&swapchainDescOld);
    swapchainDesc.Width = swapchainDescOld.BufferDesc.Width;
    swapchainDesc.Height = swapchainDescOld.BufferDesc.Height;
    swapchainDesc.Format = swapchainDescOld.BufferDesc.Format;
    swapchainDesc.Flags = swapchainDescOld.Flags;
    ThrowIfFailed(m_SwapChain->ResizeBuffers(m_FrameCount, width, height, swapchainDesc.Format, swapchainDesc.Flags));

    PE_LOG_INFO("SwapChain Resized");
}

} // namespace ProtoEngine::rhi::dx12