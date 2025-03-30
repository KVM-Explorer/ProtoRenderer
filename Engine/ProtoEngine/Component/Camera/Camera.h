#pragma once

#include <stdafx.h>
#include "ProtoEngine/Core/Type/Vec.h"
#include "ProtoEngine/Core/Type/Matrix.h"
#include "ProtoEngine/Core/Type/Quaternion.h"

namespace ProtoEngine::Component {

class Camera {
public:
    using Vec3 = Core::Vec3;
    using Vec4 = Core::Vec4;
    using Mat4 = Core::Matrix4x4;
    using Quat = Core::Quaternion;

    Camera();
    ~Camera();

    void LookAt(const Vec3 &target, const Vec3 &up, const Vec3 &position);

protected:
    virtual void UpdateViewMatrix() = 0;
    virtual void UpdateProjectionMatrix() = 0;
    virtual void UpdateViewProjectionMatrix() = 0;

    Vec3 m_Position;
    Vec3 m_Target;
    Vec3 m_Up;
    Vec3 m_Right;

    Mat4 m_ViewMatrix;
    Mat4 m_ProjectionMatrix;
    Mat4 m_ViewProjectionMatrix;
};

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
    ~OrthographicCamera();

    void SetLeft(float left);
    void SetRight(float right);
    void SetBottom(float bottom);
    void SetTop(float top);
    void SetNear(float near);
    void SetFar(float far);

    float GetLeft() const;
    float GetRight() const;
    float GetBottom() const;
    float GetTop() const;
    float GetNear() const;
    float GetFar() const;

protected:
    void UpdateViewMatrix() override;
    void UpdateProjectionMatrix() override;
    void UpdateViewProjectionMatrix() override;

private:
    float m_Left;
    float m_Right;
    float m_Bottom;
    float m_Top;
    float m_Near;
    float m_Far;
};

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspect, float near, float far);
    ~PerspectiveCamera();

    void SetFOV(float fov);
    void SetAspect(float aspect);
    void SetNear(float near);
    void SetFar(float far);

    float GetFOV() const;
    float GetAspect() const;
    float GetNear() const;
    float GetFar() const;

protected:
    void UpdateViewMatrix() override;
    void UpdateProjectionMatrix() override;
    void UpdateViewProjectionMatrix() override;

private:
    float m_FOV;
    float m_Aspect;
    float m_Near;
    float m_Far;
};
} // namespace ProtoEngine::Component