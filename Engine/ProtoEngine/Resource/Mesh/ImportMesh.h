#pragma once

#include <stdafx.h>

#include "ProtoEngine/Resource/Mesh/Mesh.h"

namespace ProtoEngine::resource {
class ImportMesh : public IMesh {
public:
    ImportMesh(std::string name, std::string path) :
        IMesh(name), m_Path(path) {}

private:
    std::string m_Path;
};
} // namespace ProtoEngine::resource