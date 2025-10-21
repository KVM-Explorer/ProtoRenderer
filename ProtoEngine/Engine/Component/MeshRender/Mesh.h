#pragma once

#include <stdafx.h>
#include "Engine/Component/IComponent.h"
#include "Engine/RHI/DX12/Resource/MeshContainer.h"
#include "Engine/RHI/DX12/Runtime/Command.h"

namespace ProtoEngine::Component {
class Mesh : public IComponent {
public:
    ComponentType GetType() const override { return ComponentType::Mesh; }

    void Init(ID3D12Device *device);
    void LoadMesh(std::string path);
    void LoadMesh(resource::MeshType type);

    void UploadGPU(rhi::dx12::GPUContext *context, rhi::dx12::CommandPool *pool);
    void Render(rhi::dx12::Command &command);

private:
    std::unique_ptr<rhi::dx12::MeshContainer> m_MeshContainer;
};

} // namespace ProtoEngine::Component