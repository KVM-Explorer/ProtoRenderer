#pragma once

#include <stdafx.h>

namespace ProtoEngine::Core {
class Quaternion {
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion &other);
};
} // namespace ProtoEngine::Core