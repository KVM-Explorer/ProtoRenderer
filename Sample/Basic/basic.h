#include "ProtoEngine.h"
#include "ProtoEngine/RHI/DX12/DX12.h"
#include "ProtoEngine/Engine.h"
#include "ProtoEngine/Framework/World/World.h"
#include "ProtoEngine/Framework/World/Entity.h"

class GPULayout : public ProtoEngine::rhi::dx12::GPUInputLayout {
public:
    void Init(ID3D12Device *device) override;
};

class BasicTriangleApp : public ProtoEngine::App {
public:
    BasicTriangleApp();
    ~BasicTriangleApp();
    void Init() override;
    void LoadAssets();
    void LoadPipeline();
    void Shutdown() override;
    void Update() override;
    void Render() override;

private:
    std::unique_ptr<ProtoEngine::rhi::dx12::GPUContext> context;
    std::unique_ptr<ProtoEngine::rhi::dx12::CommandPool> cmdPool;
    std::unique_ptr<ProtoEngine::rhi::dx12::SwapChain> swapchain;

    std::unique_ptr<GPULayout> layout;

    std::unique_ptr<ProtoEngine::rhi::dx12::FrameSyncPoint> frameSync;

    ProtoEngine::Framework::World world;
};
