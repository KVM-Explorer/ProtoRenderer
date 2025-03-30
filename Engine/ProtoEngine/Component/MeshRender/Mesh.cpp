#include "ProtoEngine/Component/MeshRender/Mesh.h"
#include "ProtoEngine/Resource/Mesh/TriangleMesh.h"
namespace ProtoEngine::Component {


void Mesh::Init(resource::MeshType type)
{
    std::shared_ptr<resource::IMesh> mesh = nullptr;
    switch (type) {
        case resource::MeshType::Triangle:
            mesh = std::make_shared<resource::TriangleMesh>();
        default:
            PE_THROW("Not implemented");
    }

    m_MeshContainer->AddVertices(mesh->GetVertices());
    m_MeshContainer->AddIndices(mesh->GetIndices());

    m_MeshContainer->Upload();
}

void Mesh::Render(rhi::dx12::Command &command)
{
    auto vbv = m_MeshContainer->GetVertexBufferView();
    auto ibv = m_MeshContainer->GetIndexBufferView();

    command.DrawCall(vbv, ibv);
}
} // namespace ProtoEngine::Component