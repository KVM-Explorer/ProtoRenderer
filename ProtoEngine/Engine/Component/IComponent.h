#pragma once

#include <stdafx.h>

namespace ProtoEngine::Component {
enum class ComponentType {
    Transform,
    Mesh,
    Camera,
    Light,
    Material,
    UI,
    Custom,
    Num
};

class IComponent {
public:
    virtual ComponentType GetType() const { return m_Type; }

protected:
    ComponentType m_Type;
};
} // namespace ProtoEngine::Component