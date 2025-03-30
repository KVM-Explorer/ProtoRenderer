#pragma once

#include <stdafx.h>

namespace ProtoEngine::Core {

class Matrix3x3 {
public:
    Matrix3x3();

private:
    float m_Matrix[3][3];
};

class Matrix4x4 {
public:
    Matrix4x4();
    // Matrix4x4(const Matrix3x3 &mat3x3);

    static Matrix4x4 Identity();

    Matrix4x4 operator*(const Matrix4x4 &other) const;
    Matrix4x4 &operator+(const Matrix4x4 &other) const;
    Matrix4x4 &operator-(const Matrix4x4 &other) const;

private:
    float m_Matrix[4][4];
};

} // namespace ProtoEngine::Core