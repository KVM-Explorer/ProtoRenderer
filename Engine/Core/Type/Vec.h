#pragma once

namespace ProtoEngine::Core {

class vec3 {
public:
    float x, y, z;

    vec3() :
        x(0.0f), y(0.0f), z(0.0f) {}
};

class vec4 {
public:
    float x, y, z, w;

    vec4() :
        x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
};

} // namespace ProtoEngine::Core
