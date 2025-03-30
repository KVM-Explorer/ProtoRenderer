#include "ProtoEngine/Resource/Mesh/TriangleMesh.h"

namespace ProtoEngine::resource {

void TriangleMesh::Init()
{
    using Core::Vec3;
    using Core::Color;
    std::array<Vertex, 3> vertices = {
        Vertex{Vec3{-0.5f, -0.5f, 0.0f}, Color{1.0f, 0.0f, 0.0f, 1.0f}},
        Vertex{Vec3{0.5f, -0.5f, 0.0f}, Color{0.0f, 1.0f, 0.0f, 1.0f}},
        Vertex{Vec3{0.0f, 0.5f, 0.0f}, Color{0.0f, 0.0f, 1.0f, 1.0f}},
    };

    m_Vertices = std::vector<Vertex>(vertices.begin(), vertices.end());
    m_Indices = std::vector<uint32>{0, 1, 2};
}

} // namespace ProtoEngine::resource