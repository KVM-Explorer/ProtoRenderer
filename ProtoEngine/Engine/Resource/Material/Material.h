#pragma once

#include <stdafx.h>

namespace ProtoEngine::resource {

enum class MaterialType {
    Opeaque,
    Transparent,
    Other,
};

enum class TextureType {
    Albedo,
    Normal,
    Roughness,
    Metallic,
    AO,
    Emissive,
    Height,
    Opacity,
    Custom,
};

class Material {
public:
    Material(std::string name) :
        m_Name(name) {}
    std::string_view GetName() const { return m_Name; }

protected:
    std::string m_Name;
};

}; // namespace ProtoEngine::resource