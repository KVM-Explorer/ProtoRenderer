#pragma once

#include <stdafx.h>
#include "ProtoEngine/Resource/Mesh/Mesh.h"

namespace ProtoEngine::resource {
class TriangleMesh : public IMesh {
public:
    TriangleMesh(std::string name = "TriangleMesh") :
        IMesh(name)
    {
        Init();
    }

private:
    void Init();
};
} // namespace ProtoEngine::resource