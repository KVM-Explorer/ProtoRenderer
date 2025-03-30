#pragma once

#include "ProtoEngine/Core/Type/Vec.h"
#include "ProtoEngine/Core/Type/Matrix.h"
#include "ProtoEngine/Core/Type/Quaternion.h"
#include "ProtoEngine/Component/IComponent.h"
namespace ProtoEngine::Component {

class Transform : public IComponent {
public:
    using Vec3 = Core::Vec3;
    using Mat4 = Core::Matrix4x4;
    using Mat3 = Core::Matrix3x3;
    using Quat = Core::Quaternion;

    ComponentType GetType() const override { return ComponentType::Transform; }

    Transform(const Vec3 &position, const Vec3 &rotation, const Vec3 &scale);
    Transform(const Transform &transform);
    Transform();

    ~Transform();

    void SetPosition(const Vec3 &position);
    void SetRotation(const Vec3 &rotation);
    void SetScale(const Vec3 &scale);

    const Vec3 &GetPosition() const;
    const Vec3 &GetRotation() const;
    const Vec3 &GetScale() const;

    void Translate(const Vec3 &translation);
    void Rotate(const Vec3 &rotation);

    void Scale(const Vec3 &scale);

    const Mat3 &GetTransformMatrix3x3() const;
    const Mat4 &GetTransformMatrix4x4() const;
    const Quat &GetQuaternion() const;

private:
    Vec3 m_Position;
    Vec3 m_Rotation;
    Vec3 m_Scale;

    Mat4 m_TransformMatrix;
    Quat m_Quaternion;

    void UpdateTransformMatrix();
};
} // namespace ProtoEngine::Component