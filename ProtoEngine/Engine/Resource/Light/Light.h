#include "Engine/Core/Type/Vec.h"
#include "Engine/Core/Type/Color.h"

namespace ProtoEngine::Resource {
using Core::Vec3;
using Core::Vec4;
using Core::Color;
struct PointLight {
    Vec3 Position;
    float Range;
    Color Color;
    float Intensity;
};

struct DirectionalLight {
    Vec3 Direction;
    float Intensity;
    Color Color;
};

struct SpotLight {
    Vec3 Position;
    float Range;
    Vec3 Direction;
    float SpotAngle;
    Color Color;
    float Intensity;
};

} // namespace ProtoEngine::Resource