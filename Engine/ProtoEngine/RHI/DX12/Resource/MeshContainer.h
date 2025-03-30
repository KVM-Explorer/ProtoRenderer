#pragma once
#include <stdafx.h>
#include "ProtoEngine/Resource/Mesh/Mesh.h"
#include "ProtoEngine/RHI/DX12/Resource/UploadBuffer.h"

namespace ProtoEngine::rhi::dx12 {

class MeshContainer {
public:
    using Vertex = ProtoEngine::resource::Vertex;
    MeshContainer(ID3D12Device *device);

    void AddVertices(std::vector<Vertex> &vertices);
    void AddIndices(std::vector<uint32> &indices);

    void Upload();

    D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() const;
    D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() const;

private:
    ID3D12Device *m_Device;

    std::vector<Vertex> m_Vertices;
    std::vector<uint32> m_Indices;

    std::unique_ptr<UploadBuffer> m_VertexBuffer;
    std::unique_ptr<UploadBuffer> m_IndexBuffer;
};

}; // namespace ProtoEngine::rhi::dx12