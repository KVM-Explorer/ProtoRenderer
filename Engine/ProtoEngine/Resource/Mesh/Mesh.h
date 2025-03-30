#pragma once

#include <stdafx.h>
#include "ProtoEngine/Core/Core.h"
namespace ProtoEngine::resource {

struct Vertex {
    using Vec3 = Core::Vec3;
    using Vec2 = Core::Vec2;
    using Color = Core::Color;

    Vec3 position;
    Color color;
};

enum class MeshType {
    Triangle,
    Cube,
    Sphere,
    Cone,
    Plane,
    Quad
};

class IMesh {
public:
    IMesh(std::string name) :
        m_Name(name) {}
    std::string_view GetName() const { return m_Name; }
    std::vector<Vertex> &GetVertices() { return m_Vertices; }
    std::vector<uint32> &GetIndices() { return m_Indices; }

protected:
    std::string m_Name;
    std::vector<Vertex> m_Vertices;
    std::vector<uint32> m_Indices;
};
} // namespace ProtoEngine::resource