#include "Engine/RHI/DX12/Resource/MeshContainer.h"
#include "Engine/RHI/DX12/Runtime/GPUContext.h"
#include "Engine/RHI/DX12/Runtime/Sync.h"

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

void MeshContainer::Upload(rhi::dx12::GPUContext *context, rhi::dx12::CommandPool *pool)
{
    // upload
    m_VBUploader = std::make_unique<UploadBuffer>(m_Device, m_Vertices.size() * sizeof(Vertex));
    m_VBUploader->CopyData(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex));
    m_IBUploader = std::make_unique<UploadBuffer>(m_Device, m_Indices.size() * sizeof(uint32));
    m_IBUploader->CopyData(m_Indices.data(), m_Indices.size() * sizeof(uint32));

    // copy
    m_VBuffer = std::make_unique<DefaultBuffer>(m_Device, m_Vertices.size() * sizeof(Vertex));
    m_IBuffer = std::make_unique<DefaultBuffer>(m_Device, m_Indices.size() * sizeof(uint32));

    auto command = pool->Allocate(CommandType::Copy, 0);
    command.Begin();

    command.Upload(m_VBuffer->Get(), m_VBUploader->Get(), m_Vertices.size() * sizeof(Vertex));
    command.Upload(m_IBuffer->Get(), m_IBUploader->Get(), m_Indices.size() * sizeof(uint32));

    command.End();

    context->Submit({&command});

    FrameSyncPoint sync(m_Device);
    sync.Signal(context);
    sync.Wait();
}

D3D12_INDEX_BUFFER_VIEW MeshContainer::GetIndexBufferView() const
{
    D3D12_INDEX_BUFFER_VIEW ibv = {};
    ibv.BufferLocation = m_IBuffer->Get()->GetGPUVirtualAddress();
    ibv.SizeInBytes = static_cast<UINT>(m_Indices.size() * sizeof(uint32));
    ibv.Format = DXGI_FORMAT_R32_UINT;
    return ibv;
}

D3D12_VERTEX_BUFFER_VIEW MeshContainer::GetVertexBufferView() const
{
    D3D12_VERTEX_BUFFER_VIEW vbv = {};
    vbv.BufferLocation = m_VBuffer->Get()->GetGPUVirtualAddress();
    vbv.SizeInBytes = static_cast<UINT>(m_Vertices.size() * sizeof(Vertex));
    vbv.StrideInBytes = sizeof(Vertex);
    return vbv;
}

} // namespace ProtoEngine::rhi::dx12