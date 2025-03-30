#include <directx/d3dx12.h>
#include "basic.h"
#include "ProtoEngine/Core/Core.h"
#include "ProtoEngine/Component/MeshRender/Mesh.h"
#include "ProtoEngine/RHI/DX12/Resource/SwapChain.h"
#include "ProtoEngine/Resource/Mesh/Mesh.h"
#include "ProtoEngine/RHI/DX12/Resource/MeshContainer.h"

namespace ProtoEngine {
std::shared_ptr<ProtoEngine::App> CreateApp()
{
    return std::make_shared<BasicTriangleApp>();
}
} // namespace ProtoEngine

void GPULayout::Init(ID3D12Device *device)
{
    auto compiler = ProtoEngine::rhi::dx12::ShaderCompiler::GetInstance();

    auto vs = compiler->Compile("../Shader/Basic/basic.hlsl", "VSMain", "vs_6_0");
    auto ps = compiler->Compile("../Shader/Basic/basic.hlsl", "PSMain", "ps_6_0");

    vs.GetRootSignature(device, m_Signature);

    D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateDesc = {};
    pipelineStateDesc.InputLayout = vs.GetInputLayout();
    pipelineStateDesc.pRootSignature = m_Signature.Get();
    pipelineStateDesc.VS = vs.GetShaderByteCode();
    pipelineStateDesc.PS = ps.GetShaderByteCode();
    pipelineStateDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    pipelineStateDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    pipelineStateDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
    pipelineStateDesc.DepthStencilState.DepthEnable = false;
    pipelineStateDesc.DepthStencilState.StencilEnable = false;
    pipelineStateDesc.SampleMask = UINT_MAX;
    pipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    pipelineStateDesc.NumRenderTargets = 1;
    pipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    pipelineStateDesc.SampleDesc.Count = 1;
    ThrowIfFailed(device->CreateGraphicsPipelineState(&pipelineStateDesc, IID_PPV_ARGS(&m_PSO)));
}

BasicTriangleApp::BasicTriangleApp() :
    App(1920, 1080, "BasicTriangle")
{
}

BasicTriangleApp::~BasicTriangleApp()
{
}

void BasicTriangleApp::Init()
{
    context = std::make_unique<ProtoEngine::rhi::dx12::GPUContext>();
    cmdPool = std::make_unique<ProtoEngine::rhi::dx12::CommandPool>(*context);
    auto allocator = ProtoEngine::rhi::dx12::ResourceAllocator::GetInstance();
    allocator->Init(context->GetDevice());

    swapchain = std::make_unique<ProtoEngine::rhi::dx12::SwapChain>(*context, m_Width, m_Height);

    LoadPipeline();
    LoadAssets();

    // Fence
    frameSync = std::make_unique<ProtoEngine::rhi::dx12::FrameSyncPoint>(context->GetDevice());
}

void BasicTriangleApp::LoadPipeline()
{
    layout = std::make_unique<GPULayout>();

    layout->Init(context->GetDevice());
}

void BasicTriangleApp::LoadAssets()
{
    ProtoEngine::Framework::Entity entity("NDC Triangle");
    auto meshComponent = std::make_shared<ProtoEngine::Component::Mesh>();

    meshComponent->Init(context->GetDevice());
    meshComponent->LoadMesh(ProtoEngine::resource::MeshType::Triangle);
    meshComponent->UploadGPU(context.get(), cmdPool.get());

    entity.AddComponent(meshComponent);

    world.AddEntity(entity);
}

void BasicTriangleApp::Update()
{
}

void BasicTriangleApp::Record()
{
    auto command = cmdPool->Allocate(ProtoEngine::rhi::dx12::CommandType::Graphics, 0);

    // Begin Render
    command.Begin();
    command.BindGPULayout(layout.get());
    command.SetScreenView({1920, 1080}, {1920, 1080});

    auto [viewId, resId] = swapchain->GetCurrentRT();

    // Convert
    auto allocator = ProtoEngine::rhi::dx12::ResourceAllocator::GetInstance();
    auto resource = allocator->GetResource(resId);
    auto barrier1 = CD3DX12_RESOURCE_BARRIER::Transition(resource, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
    command.ResourceBarrier({barrier1});

    // DrawCall
    command.ClearRT({viewId}, std::nullopt);

    world.Render(command);

    // Convert
    auto barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(resource, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
    command.ResourceBarrier({barrier2});
    command.End();

    context->Submit({&command});
}

void BasicTriangleApp::Render()
{
    Record();

    swapchain->Present();

    frameSync->Signal(context.get());
    frameSync->Wait();
}

void BasicTriangleApp::AfterTick()
{
    // TODO: 重新设计Command的回收和Allocator-Resource的回收
    cmdPool->EndFrame();
    swapchain->MoveNextFrame();
}

void BasicTriangleApp::Shutdown()
{
    // Resource Cleanup

    // Shader Cleanup
    frameSync = nullptr;
    cmdPool = nullptr;
    layout = nullptr;
    ProtoEngine::rhi::dx12::ShaderCompiler::GetInstance()->Release();

    swapchain = nullptr;
    context = nullptr;
}
