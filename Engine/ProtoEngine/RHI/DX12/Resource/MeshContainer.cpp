#include "ProtoEngine/RHI/DX12/Resource/MeshContainer.h"

namespace ProtoEngine::rhi::dx12 {

MeshContainer::MeshContainer(ID3D12Device *device) :
    m_Device(device)
{
}

void MeshContainer::AddVertices(std::vector<Vertex> &vertices)
{
    m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
}

void MeshContainer::AddIndices(std::vector<uint32> &indices)
{
    m_Indices.insert(m_Indices.end(), indices.begin(), indices.end());
}

void MeshContainer::Upload()
{
    m_VertexBuffer = std::make_unique<UploadBuffer>(m_Device, m_Vertices.size() * sizeof(Vertex));
    m_VertexBuffer->CopyData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
    m_IndexBuffer = std::make_unique<UploadBuffer>(m_Device, m_Indices.size() * sizeof(uint32));
    m_IndexBuffer->CopyData(m_Indices.data(), m_Indices.size() * sizeof(uint32));
}

D3D12_INDEX_BUFFER_VIEW MeshContainer::GetIndexBufferView() const
{
    D3D12_INDEX_BUFFER_VIEW ibv = {};
    ibv.BufferLocation = m_IndexBuffer->Get()->GetGPUVirtualAddress();
    ibv.SizeInBytes = static_cast<UINT>(m_Indices.size() * sizeof(uint32));
    ibv.Format = DXGI_FORMAT_R32_UINT;
    return ibv;
}

D3D12_VERTEX_BUFFER_VIEW MeshContainer::GetVertexBufferView() const
{
    D3D12_VERTEX_BUFFER_VIEW vbv = {};
    vbv.BufferLocation = m_VertexBuffer->Get()->GetGPUVirtualAddress();
    vbv.SizeInBytes = static_cast<UINT>(m_Vertices.size() * sizeof(Vertex));
    vbv.StrideInBytes = sizeof(Vertex);
    return vbv;
}

} // namespace ProtoEngine::rhi::dx12