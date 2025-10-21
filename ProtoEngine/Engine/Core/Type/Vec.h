#pragma once

namespace ProtoEngine::Core {

class Vec2 {
public:
    float x, y;

    Vec2() :
        x(0.0f), y(0.0f) {}
    Vec2(float x, float y) :
        x(x), y(y) {}
};

class Vec3 {
public:
    float x, y, z;

    Vec3() :
        x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) :
        x(x), y(y), z(z) {}
};

class Vec4 {
public:
    float x, y, z, w;

    Vec4() :
        x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
};

} // namespace ProtoEngine::Core
