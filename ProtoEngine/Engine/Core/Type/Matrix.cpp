#include "Engine/Core/Type/Matrix.h"

namespace ProtoEngine::Core {

Matrix3x3::Matrix3x3()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_Matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Matrix4x4 Matrix4x4::Identity()
{
    return Matrix4x4();
}
Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m_Matrix[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
{
    Matrix4x4 ret;
    return ret;
}

} // namespace ProtoEngine::Core