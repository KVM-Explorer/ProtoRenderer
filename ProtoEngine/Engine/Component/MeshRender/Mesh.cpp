#include "Engine/Component/MeshRender/Mesh.h"
#include "Engine/Resource/Mesh/TriangleMesh.h"
namespace ProtoEngine::Component {

void Mesh::Init(ID3D12Device *device)
{
    m_MeshContainer = std::make_unique<rhi::dx12::MeshContainer>(device);
}

void Mesh::LoadMesh(std::string path)
{
    PE_THROW("Mesh loading is not implemented yet");
}

void Mesh::LoadMesh(resource::MeshType type)
{
    std::shared_ptr<resource::IMesh> mesh = nullptr;
    switch (type) {
    case resource::MeshType::Triangle:
        mesh = std::make_shared<resource::TriangleMesh>();
        break;
    default:
        PE_THROW("Not implemented");
    }

    m_MeshContainer->AddVertices(mesh->GetVertices());
    m_MeshContainer->AddIndices(mesh->GetIndices());
}

void Mesh::UploadGPU(rhi::dx12::GPUContext *context, rhi::dx12::CommandPool *pool)
{
    m_MeshContainer->Upload(context, pool);
}

void Mesh::Render(rhi::dx12::Command &command)
{
    auto vbv = m_MeshContainer->GetVertexBufferView();
    auto ibv = m_MeshContainer->GetIndexBufferView();

    command.DrawCall(vbv, ibv);
}
} // namespace ProtoEngine::Component