
#include "Engine/Component/Camera/Camera.h"
#include "Engine/Core/Type/Matrix.h"
#include "Engine/Core/Type/Vec.h"
#include "Engine/Core/Type/Quaternion.h"

namespace ProtoEngine::Component {

// Camera类的构造函数
Camera::Camera() :
    m_Position(Core::Vec3()),
    m_Target(Core::Vec3()),
    m_Up(Core::Vec3(0.0f, 1.0f, 0.0f)),
    m_Right(Core::Vec3(0.0f, 0.0f, 1.0f)),
    m_ViewMatrix(Core::Matrix4x4::Identity()),
    m_ProjectionMatrix(Core::Matrix4x4::Identity()),
    m_ViewProjectionMatrix(Core::Matrix4x4::Identity())
{
}

// Camera类的析构函数
Camera::~Camera()
{
}

// Camera类的LookAt方法
void Camera::LookAt(const Vec3 &target, const Vec3 &up, const Vec3 &position)
{
    m_Target = target;
    m_Up = up;
    m_Position = position;
    UpdateViewMatrix();
    UpdateViewProjectionMatrix();
}

// OrthographicCamera类的构造函数
OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) :
    m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top), m_Near(near), m_Far(far)
{
    UpdateProjectionMatrix();
    UpdateViewProjectionMatrix();
}

// OrthographicCamera类的析构函数
OrthographicCamera::~OrthographicCamera()
{
}

// OrthographicCamera类的设置左边界方法
void OrthographicCamera::SetLeft(float left)
{
    m_Left = left;
    UpdateProjectionMatrix();
    UpdateViewProjectionMatrix();
}

// 其他Set方法实现类似，省略...

// OrthographicCamera类的获取左边界方法
float OrthographicCamera::GetLeft() const
{
    return m_Left;
}

// 其他Get方法实现类似，省略...

// OrthographicCamera类的更新视图矩阵方法
void OrthographicCamera::UpdateViewMatrix()
{
    // 实现视图矩阵更新逻辑
}

// OrthographicCamera类的更新投影矩阵方法
void OrthographicCamera::UpdateProjectionMatrix()
{
    // 实现投影矩阵更新逻辑
}

// OrthographicCamera类的更新视图投影矩阵方法
void OrthographicCamera::UpdateViewProjectionMatrix()
{
    m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
}

// PerspectiveCamera类的构造函数
PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float near, float far) :
    m_FOV(fov), m_Aspect(aspect), m_Near(near), m_Far(far)
{
    UpdateProjectionMatrix();
    UpdateViewProjectionMatrix();
}

// PerspectiveCamera类的析构函数
PerspectiveCamera::~PerspectiveCamera()
{
}

// PerspectiveCamera类的设置FOV方法
void PerspectiveCamera::SetFOV(float fov)
{
    m_FOV = fov;
    UpdateProjectionMatrix();
    UpdateViewProjectionMatrix();
}

// 其他Set方法实现类似，省略...

// PerspectiveCamera类的获取FOV方法
float PerspectiveCamera::GetFOV() const
{
    return m_FOV;
}

// 其他Get方法实现类似，省略...

// PerspectiveCamera类的更新视图矩阵方法
void PerspectiveCamera::UpdateViewMatrix()
{
    // 实现视图矩阵更新逻辑
}

// PerspectiveCamera类的更新投影矩阵方法
void PerspectiveCamera::UpdateProjectionMatrix()
{
    // 实现投影矩阵更新逻辑
}

// PerspectiveCamera类的更新视图投影矩阵方法
void PerspectiveCamera::UpdateViewProjectionMatrix()
{
    m_ViewProjectionMatrix = m_ViewMatrix * m_ProjectionMatrix;
}

} // namespace ProtoEngine::Component