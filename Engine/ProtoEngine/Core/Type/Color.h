#pragma once

namespace ProtoEngine::Core {

class Color

{
public:
    float r, g, b, a;

    Color() :
        r(0.0f), g(0.0f), b(0.0f), a(0.0f)
    {}

    Color(float r, float g, float b, float a) :
        r(r), g(g), b(b), a(a)
    {}
};

} // namespace ProtoEngine::Core
